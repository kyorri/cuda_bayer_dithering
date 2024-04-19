#include "BayerDithering.h"

#include <cmath>
#include <algorithm>

namespace bayer_dithering {
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

    uint8_t dither_size = std::sqrt(dither.size());

    auto max_threshold = std::max_element(dither.begin(), dither.end());
    uint32_t multiplier = 256 / *max_threshold;

    std::vector<Pixel>& img_pixels = _img.GetBuffer();
    uint32_t width = _img.GetWidth();
    uint32_t height = _img.GetHeight();

    for (uint32_t y = 0; y < height; ++y) {
        for (uint32_t x = 0; x < width; ++x) {
            uint32_t dither_idx = (y % dither_size) * dither_size + (x % dither_size);
            uint8_t threshold = dither[dither_idx] * multiplier;
            uint32_t flipped_idx = ((height - 1 - y) * width) + x;
            Pixel& p = img_pixels[flipped_idx];
            p = (p.r > threshold || p.g > threshold || p.b > threshold) ? Pixel(255) : Pixel(0);
        }
    }
};

} // namespace bayer_dithering
