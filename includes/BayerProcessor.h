#pragma once

#include "Image.h"
#include "BayerDithering.h"

namespace bayer_dithering {
    class BayerProcessor {
    public:
        BayerProcessor() = default;
        void ProcessImages(std::vector<std::pair<Image&, Image&>>);
    };
} // namespace bayer_dithering
