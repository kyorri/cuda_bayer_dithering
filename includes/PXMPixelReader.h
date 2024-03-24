#pragma once

#include "Pixel.h"
#include "Image.h"

#include <fstream>
#include <filesystem>
#include <vector>

namespace bayer_dithering {
	class PXMPixelReader {
	public:
		virtual Image Read(std::fstream&) = 0;
	};
} // namespace bayer_dithering

