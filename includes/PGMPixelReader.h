#pragma once

#include "PXMPixelReader.h"

namespace bayer_dithering {
	class PGMPixelReader : public PXMPixelReader {
	public:
		Image Read(std::fstream&) override;
	};
} // namespace bayer_dithering