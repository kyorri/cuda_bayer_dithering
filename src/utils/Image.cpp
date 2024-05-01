#include "Image.h"

#include <algorithm>

namespace bayer_dithering {
    Image::Image(uint32_t _w, uint32_t _h, std::vector<Pixel> _buffer) : w_(_w), h_(_h), buffer_(_buffer) {}

    uint32_t Image::GetWidth() {
        return w_;
    }

    uint32_t Image::GetHeight() {
        return h_;
    }

    Pixel& Image::GetPixel(uint32_t _x, uint32_t _y) {
        return buffer_[_y * w_ + _x];
    }

    std::vector<Pixel>& Image::GetBuffer() {
        return buffer_;
    }

    void Image::SetBuffer(std::vector<Pixel>& _buffer) {
        buffer_ = _buffer;
    }

    void Image::ConvertGrayscale()
    {
        std::for_each(buffer_.begin(), buffer_.end(), [](Pixel& p) {
            p.ConvertGrayscale();
        });
    }

} // namespace bayer_dithering 
