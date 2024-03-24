#include "NetpbmReader.h"

#include <iostream>

namespace bayer_dithering {
NetpbmReader::NetpbmReader(std::filesystem::path __filepath) : filestream_(std::fstream(__filepath)) {
    filestream_ >> magic_number;
};

NetpbmReader::~NetpbmReader() {
    if (!filestream_.is_open()) {
        filestream_.close();
    }
};

std::string NetpbmReader::GetMagicNumber() {
    return magic_number;
};

Image NetpbmReader::Read() {
    PXMPixelReader* pixel_reader;
    if (magic_number.compare("P1") == 0) {
        pixel_reader = new PBMPixelReader();
    } else if (magic_number.compare("P2") == 0) {
        pixel_reader = new PGMPixelReader();
    } else if (magic_number.compare("P3") == 0) {
        pixel_reader = new PPMPixelReader();
    } else {
        throw std::invalid_argument("Invalid \"magic number\" in the image file header!");
    }
    Image outs = pixel_reader->Read(filestream_);
    return outs;
};

} // namespace bayer_dithering
