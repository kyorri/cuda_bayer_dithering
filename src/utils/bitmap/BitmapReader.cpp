#include "BitmapReader.h"

#include <algorithm>

namespace bayer_dithering {



    Image BitmapReader::ReadBitmapImage(std::filesystem::path file_path) {

        std::ifstream bmp_file(file_path, std::ios::in | std::ios::binary);

        if (!bmp_file.is_open()) {
            throw std::runtime_error("Error: File could not be opened!");
        }

        const uint32_t file_header_size = 14;
        const uint32_t info_header_size = 40;

        uint8_t file_header[file_header_size] = {};
        bmp_file.read(reinterpret_cast<char*>(file_header), file_header_size);
        
        if (file_header[0] != 'B' || file_header[1] != 'M') {
            throw std::runtime_error("Error: Wrong file contents!");
        }
        
        uint8_t info_header[info_header_size] = {};
        bmp_file.read(reinterpret_cast<char*>(info_header), info_header_size);

        uint32_t file_size = (file_header[2]) + (file_header[3] << 8) + (file_header[4] << 16) + (file_header[5] << 24);
        uint32_t width = (info_header[4]) + (info_header[5] << 8) + (info_header[6] << 16) + (info_header[7] << 24);
        uint32_t height = (info_header[8]) + (info_header[9] << 8) + (info_header[10] << 16) + (info_header[11] << 24);

        std::vector<Pixel> img_pixel_data(width * height, Pixel());

        const uint32_t padding = ((4 - (width * 3) % 4) % 4);

        //for (uint32_t y = height - 1; y >= 0; y--) {

        for (uint32_t y = 0; y < height; y++) {
            for (uint32_t x = 0; x < width; x++) {

                uint8_t pixel_channel[3] = {};
                bmp_file.read(reinterpret_cast<char*>(pixel_channel), 3);

                Pixel& pixel = img_pixel_data[y * width + x];

                pixel.r = static_cast<float>(pixel_channel[2]) / 255.0f;
                pixel.g = static_cast<float>(pixel_channel[1]) / 255.0f;
                pixel.b = static_cast<float>(pixel_channel[0]) / 255.0f;
            }
            bmp_file.ignore(padding);
        }
        bmp_file.close();

        return Image(width, height, img_pixel_data);
    }

} // namespace bayer_dithering