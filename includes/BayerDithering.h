#pragma once

#include "Image.h"

namespace bayer_dithering {
class BayerDithering {
public:
    BayerDithering() = default;
    void ProcessImage(Image&);
};
} // namespace bayer_dithering
