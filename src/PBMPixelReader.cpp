#include "PBMPixelReader.h"

namespace bayer_dithering {
	Image PBMPixelReader::Read(std::fstream& _filestream) {
		uint32_t _w, _h;
		_filestream >> _w >> _h;

		std::vector<Pixel> _contents;
		for (int i = 0; i < _w * _h; i++) {
			uint32_t __val;
			_filestream >> __val;
			uint32_t bnw_value = 255 - (__val * 255);
			_contents.emplace_back(bnw_value);
		}

		Image outs(_w, _h, _contents);
		return outs;
	}
}