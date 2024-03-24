#pragma once

#include "PXMPixelReader.h"
#include "PBMPixelReader.h"
#include "PGMPixelReader.h"
#include "PPMPixelReader.h"

namespace bayer_dithering {
class NetpbmReader {
public:
    NetpbmReader(std::filesystem::path);
    ~NetpbmReader();
    Image Read();
    std::string GetMagicNumber();
private:
    std::fstream filestream_;
    std::string magic_number;
};
    
} // namespace bayer_dithering
