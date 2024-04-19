#include "BitmapReader.h"

#include <algorithm>

namespace bayer_dithering {

    #pragma pack(push, 1)
    struct BitmapFileHeader {
        uint16_t type;
        uint32_t file_size;
        uint16_t reserved1;
        uint16_t reserved2;
        uint32_t offset_data;
    };

    struct BitmapInfoHeader {
        uint32_t size;
        int32_t width;
        int32_t height;
        uint16_t planes;
        uint16_t bit_count;
        uint32_t compression;
        uint32_t size_image;
        int32_t x_pixels_per_meter;
        int32_t y_pixels_per_meter;
        uint32_t colors_used;
        uint32_t colors_important;
    };
    #pragma pack(pop)

    Image BitmapReader::ReadBitmapImage(std::filesystem::path file_path) {
        std::ifstream bmp_file(file_path, std::ios::binary);
        if (!bmp_file.is_open()) {
            throw std::runtime_error("Error: Unable to open BMP file " + file_path.string());
        }

        BitmapFileHeader file_header;
        bmp_file.read(reinterpret_cast<char*>(&file_header), sizeof(file_header));

        BitmapInfoHeader info_header;
        bmp_file.read(reinterpret_cast<char*>(&info_header), sizeof(info_header));

        if (file_header.type != 0x4D42 || info_header.bit_count != 24 || info_header.compression != 0) {
            throw std::runtime_error("Error: Invalid BMP file format");
        }

        uint32_t width = info_header.width;
        uint32_t height = info_header.height;

        uint32_t row_size = (width * 3 + 3) & (~3);

        std::vector<Pixel> pixels;
        pixels.reserve(width * height);
        for (int y = height - 1; y >= 0; y--) {
            for (int x = 0; x < width; x++) {
                Pixel pixel;
                bmp_file.read(reinterpret_cast<char*>(&pixel.b), 1);
                bmp_file.read(reinterpret_cast<char*>(&pixel.g), 1);
                bmp_file.read(reinterpret_cast<char*>(&pixel.r), 1);
                pixels.push_back(pixel);
            }
            
            bmp_file.seekg(row_size - width * 3, std::ios::cur);
        }
        std::reverse(pixels.begin(), pixels.end());


        bmp_file.close();

        return Image(width, height, pixels);
    }

} // namespace bayer_dithering