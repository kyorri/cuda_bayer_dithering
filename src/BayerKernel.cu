#include "BayerDithering.h"

#include "Image.h"

#include <cmath>
#include <algorithm>

#include <cuda.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

namespace bayer_dithering {
    __global__ void BayerDitheringKernel(Pixel *img_pixels, uint32_t width, uint32_t height, uint8_t *dither, uint8_t dither_size, uint32_t multiplier) {
        int x = blockIdx.x * blockDim.x + threadIdx.x;
        int y = blockIdx.y * blockDim.y + threadIdx.y;

        if (x < width && y < height) {
            uint32_t dither_idx = (y % dither_size) * dither_size + (x % dither_size);
            uint8_t threshold = dither[dither_idx] * multiplier;
            uint32_t flipped_idx = ((height - 1 - y) * width) + x;
            Pixel& p = img_pixels[flipped_idx];
            p = (p.r > threshold || p.g > threshold || p.b > threshold) ? Pixel(255) : Pixel(0);
        }
    }

    void BayerDithering::ProcessImageParallel(Image& _img) {
        _img.ConvertGrayscale();

        std::vector<uint8_t> dither { 0, 32, 8, 40, 2, 34, 10, 42,
                                    48, 16, 56, 24, 50, 18, 58, 26,
                                    12, 44, 4, 36, 14, 46, 6, 38,
                                    60, 28, 52, 20, 62, 30, 54, 22,
                                    3, 35, 11, 43, 1, 33, 9, 41,
                                    51, 19, 59, 27, 49, 17, 57, 25,
                                    15, 47, 7, 39, 13, 45, 5, 37,
                                    63, 31, 55, 23, 61, 29, 53, 21};

        uint8_t dither_size = std::sqrt(dither.size());
        auto max_threshold = std::max_element(dither.begin(), dither.end());
        uint32_t multiplier = 256 / *max_threshold;

        std::vector<Pixel>& img_pixels = _img.GetBuffer();
        uint32_t width = _img.GetWidth();
        uint32_t height = _img.GetHeight();

        Pixel* d_img_pixels;
        uint8_t* d_dither;

        cudaMalloc(&d_img_pixels, width * height * sizeof(Pixel));
        cudaMalloc(&d_dither, dither.size() * sizeof(uint8_t));

        cudaMemcpy(d_img_pixels, img_pixels.data(), width * height * sizeof(Pixel), cudaMemcpyHostToDevice);
        cudaMemcpy(d_dither, dither.data(), dither.size() * sizeof(uint8_t), cudaMemcpyHostToDevice);

        dim3 blockDim(16, 16);
        dim3 gridDim((width + blockDim.x - 1) / blockDim.x, (height + blockDim.y - 1) / blockDim.y);

        BayerDitheringKernel<<<gridDim, blockDim>>>(d_img_pixels, width, height, d_dither, dither_size, multiplier);

        cudaMemcpy(img_pixels.data(), d_img_pixels, width * height * sizeof(Pixel), cudaMemcpyDeviceToHost);

        cudaFree(d_img_pixels);
        cudaFree(d_dither);
    }

} // namespace bayer_dithering 
