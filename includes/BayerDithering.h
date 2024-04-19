#pragma once

#include "Image.h"

#include <cstdint>

namespace bayer_dithering {
class BayerDithering {
public:
    BayerDithering() = default;
    void ProcessImageSerial(Image&);
    void ProcessImageParallel(Image&, uint32_t, uint32_t);
};
} // namespace bayer_dithering
