#include "BayerDithering.h"

#include <cmath>
#include <algorithm>

namespace bayer_dithering {
void BayerDithering::ProcessImage(Image& _img) {
    _img.ConvertGrayscale();

    std::vector<uint8_t> dither { 0, 32, 8, 40, 2, 34, 10, 42,
                                48, 16, 56, 24, 50, 18, 58, 26,
                                12, 44, 4, 36, 14, 46, 6, 38,
                                60, 28, 52, 20, 62, 30, 54, 22,
                                3, 35, 11, 43, 1, 33, 9, 41,
                                51, 19, 59, 27, 49, 17, 57, 25,
                                15, 47, 7, 39, 13, 45, 5, 37,
                                63, 31, 55, 23, 61, 29, 53, 21};

    auto it = dither.begin();
    std::vector<Pixel>& img_pixels = _img.GetBuffer();

    auto max_threshold = std::max_element(dither.begin(), dither.end());
    uint32_t multiplier = 256 / *max_threshold;

    std::for_each(img_pixels.begin(), img_pixels.end(), 
        [&dither, &it, multiplier] (Pixel& p) {
            uint8_t threshold;
            if (it != dither.end()) {
                it++;
            } else {
                it = dither.begin();
            }
            threshold = *it * multiplier;
            std::get<0>(p.Get()) > threshold ? p.Set(255) : p.Set(0);
        });
};

} // namespace bayer_dithering
