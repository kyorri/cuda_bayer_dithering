#include "BayerDithering.h"

#include <cmath>
#include <algorithm>
#include <iostream>

namespace bayer_dithering {

    uint8_t map_dither_host(uint8_t x, uint8_t in_min, uint8_t in_max, uint8_t out_min, uint8_t out_max) {
        return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    }

    void BayerDithering::ProcessImageSerial(Image& _img) {

        _img.ConvertGrayscale();

        std::vector<uint8_t> dither { 0, 32, 8, 40, 2, 34, 10, 42,
                                      48, 16, 56, 24, 50, 18, 58, 26,
                                      12, 44, 4, 36, 14, 46, 6, 38,
                                      60, 28, 52, 20, 62, 30, 54, 22,
                                      3, 35, 11, 43, 1, 33, 9, 41,
                                      51, 19, 59, 27, 49, 17, 57, 25,
                                      15, 47, 7, 39, 13, 45, 5, 37,
                                      63, 31, 55, 23, 61, 29, 53, 21};

        std::vector<Pixel>& img_pixels = _img.GetBuffer();
        uint8_t dither_size = static_cast<uint8_t>(std::sqrt(dither.size()));
        uint32_t width = _img.GetWidth();
        uint32_t height = _img.GetHeight();

        for (uint32_t y = 0; y < height; y++) {
            for (uint32_t x = 0; x < width; x++) {

                uint32_t dither_idx = (y % dither_size) * dither_size + (x % dither_size);
                uint8_t dither_value = map_dither_host(dither[dither_idx], 0, dither_size * dither_size - 1, 0, 255);
                float threshold = static_cast<float>(dither_value) / 255.0f;

                float new_value = 0.0f;
                Pixel& p = img_pixels[y * width + x];
                if (p.r >= threshold || p.b >= threshold || p.g >= threshold) {
                    new_value = 1.0f;
                }
                p.r = p.g = p.b = new_value;
            }
        }

    };

} // namespace bayer_dithering
