#pragma once

#include "Image.h"
#include "BayerDithering.h"
#include "BitmapReader.h"
#include "BitmapWriter.h"

#include <vector>
#include <string>
#include <filesystem>

namespace bayer_dithering {
    class BayerProcessor {
    public:
        BayerProcessor();
        BayerProcessor(std::filesystem::path, std::filesystem::path);
        void ProcessImages();
    private:
        std::filesystem::path in_directory_;
        std::filesystem::path out_directory_;
    };
} // namespace bayer_dithering
