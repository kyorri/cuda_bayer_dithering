#include "BayerDithering.h"

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <cmath>
#include <algorithm>

namespace bayer_dithering {

    __device__ uint8_t map_dither_device(uint8_t x, uint8_t in_min, uint8_t in_max, uint8_t out_min, uint8_t out_max) {
        return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    }

    __global__ void DitheringKernel(Pixel* in_pixels, Pixel* out_pixels, uint32_t width, uint32_t height) {
        uint8_t dither[64] = { 0, 32, 8, 40, 2, 34, 10, 42,
                        48, 16, 56, 24, 50, 18, 58, 26,
                        12, 44, 4, 36, 14, 46, 6, 38,
                        60, 28, 52, 20, 62, 30, 54, 22,
                        3, 35, 11, 43, 1, 33, 9, 41,
                        51, 19, 59, 27, 49, 17, 57, 25,
                        15, 47, 7, 39, 13, 45, 5, 37,
                        63, 31, 55, 23, 61, 29, 53, 21 };
        uint8_t dither_size = 8;

        uint32_t x = blockIdx.x * blockDim.x + threadIdx.x;
        uint32_t y = blockIdx.y * blockDim.y + threadIdx.y;

        if (x < width && y < height) {
            uint32_t dither_idx = (y % dither_size) * dither_size + (x % dither_size);
            uint8_t dither_value = map_dither_device(dither[dither_idx], 0, dither_size * dither_size - 1, 0, 255);
            float threshold = static_cast<float>(dither_value);

            Pixel p = in_pixels[y * width + x];
            float new_value = 0.0f;

            float accuracy = 1.0f / 256.0f;
            
            if (p.r > threshold - accuracy || p.b > threshold - accuracy || p.g > threshold - accuracy) {
                new_value = 1.0f;
            }

            out_pixels[y * width + x].r = new_value;
            out_pixels[y * width + x].g = new_value;
            out_pixels[y * width + x].b = new_value;
        }
    }



    void BayerDithering::ProcessImageParallel(Image& _img, uint32_t blockX, uint32_t blockY) {
        
        std::vector<Pixel>& img_pixels = _img.GetBuffer();
        uint32_t width = _img.GetWidth();
        uint32_t height = _img.GetHeight();

        Pixel* in_image;
        Pixel* out_image;

        cudaMallocManaged(&in_image, width * height * sizeof(Pixel));
        cudaMallocManaged(&out_image, width * height * sizeof(Pixel));

        cudaMemcpy(in_image, img_pixels.data(), width * height * sizeof(Pixel), cudaMemcpyHostToDevice);

        dim3 blockDim(blockX, blockY);
        dim3 gridDim((width + blockX - 1) / blockX, (height + blockY - 1) / blockY);

        DitheringKernel<<<gridDim, blockDim >>>(in_image, out_image, width, height);

        cudaDeviceSynchronize();
        cudaMemcpy(img_pixels.data(), out_image, width * height * sizeof(Pixel), cudaMemcpyDeviceToHost);

        _img.SetBuffer(img_pixels);

        cudaFree(in_image);
        cudaFree(out_image);
    }

} // namespace bayer_dithering
