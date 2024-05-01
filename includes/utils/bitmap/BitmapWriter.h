#pragma once

#include "Image.h"

#include <iostream>
#include <fstream>
#include <filesystem>

namespace bayer_dithering {
class BitmapWriter {
public:
    void WriteBitmapImage(Image&, std::filesystem::path);
};
} // namespace bayer_dithering
