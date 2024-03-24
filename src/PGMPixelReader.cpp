#include "PGMPixelReader.h"

namespace bayer_dithering {
	Image PGMPixelReader::Read(std::fstream& _filestream) {
		uint32_t _w, _h;
		_filestream >> _w >> _h;

        uint32_t max_value;
        _filestream >> max_value;

		std::vector<Pixel> _contents;
		for (int i = 0; i < _w * _h; i++) {
			uint32_t __val;
			_filestream >> __val;
            uint32_t grayscale_value = static_cast<uint32_t>(__val * (256 / max_value));
			_contents.emplace_back(grayscale_value);
		}

		Image outs(_w, _h, _contents);
		return outs;
	}
}