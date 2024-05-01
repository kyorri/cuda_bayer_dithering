#pragma once

#include "Image.h"

#include <iostream>
#include <fstream>
#include <filesystem>

namespace bayer_dithering {
class BitmapReader {
public:
    Image ReadBitmapImage(std::filesystem::path);
};
} // namespace bayer_dithering
