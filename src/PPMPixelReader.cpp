#include "PPMPixelReader.h"

namespace bayer_dithering {
	Image PPMPixelReader::Read(std::fstream& _filestream) {
		uint32_t _w, _h;
		_filestream >> _w >> _h;

        uint32_t max_value;
        _filestream >> max_value;
        if (max_value == 0) {
            throw std::runtime_error("The channels' max value cannot be a null value!");
        }

		std::vector<Pixel> _contents;
		for (int i = 0; i < _w * _h; i++) {
			uint32_t __val_r, __val_g, __val_b;
			_filestream >> __val_r >> __val_g >> __val_b;
            uint32_t color_value_r = static_cast<uint32_t>(__val_r * (256 / max_value));
            uint32_t color_value_g = static_cast<uint32_t>(__val_g * (256 / max_value));
            uint32_t color_value_b = static_cast<uint32_t>(__val_b * (256 / max_value));
			_contents.emplace_back(color_value_r, color_value_g, color_value_b);
		}

		Image outs(_w, _h, _contents);
		return outs;
	}
}