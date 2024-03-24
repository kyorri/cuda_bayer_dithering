#pragma once

#include "Pixel.h"

#include <vector>
#include <cstdint>

namespace bayer_dithering {
class Image {
public:
    Image(uint32_t, uint32_t, std::vector<Pixel>);
    void ConvertGrayscale();

    uint32_t GetWidth();
    uint32_t GetHeight();
    std::vector<Pixel>& GetBuffer();
private:
    uint32_t w_;
    uint32_t h_;
    std::vector<Pixel> buffer_;
};
} // namespace bayer_dithering
