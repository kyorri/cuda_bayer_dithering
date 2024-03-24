#pragma once

#include "PXMPixelReader.h"

namespace bayer_dithering {
	class PPMPixelReader : public PXMPixelReader {
	public:
		Image Read(std::fstream&) override;
	};
} // namespace bayer_dithering