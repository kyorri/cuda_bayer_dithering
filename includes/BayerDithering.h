#pragma once

#include "Image.h"

namespace bayer_dithering {
class BayerDithering {
public:
    BayerDithering() = default;
    void ProcessImageSerial(Image&);
    void ProcessImageParallel(Image&);
};
} // namespace bayer_dithering
