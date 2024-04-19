#include "BitmapWriter.h"

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
void FlipPixelsHorizontally(std::vector<Pixel>& pixels, uint32_t width, uint32_t height) {
    for (uint32_t y = 0; y < height; ++y) {
        for (uint32_t x = 0; x < width / 2; ++x) {
            std::swap(pixels[y * width + x], pixels[y * width + (width - 1 - x)]);
        }
    }
}


    void BitmapWriter::WriteBitmapImage(Image& img_data, std::filesystem::path file_path) {
        uint32_t width = img_data.GetWidth();
        uint32_t height = img_data.GetHeight();

        BitmapFileHeader file_header;
        BitmapInfoHeader info_header;

        file_header.type = 0x4D42; // 'BM'
        file_header.reserved1 = 0;
        file_header.reserved2 = 0;
        file_header.offset_data = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader);

        info_header.size = sizeof(BitmapInfoHeader);
        info_header.width = width;
        info_header.height = height;
        info_header.planes = 1;
        info_header.bit_count = 24;
        info_header.compression = 0;

        uint32_t row_size = (width * 3 + 3) & (~3);
        uint32_t image_size = row_size * height;

        info_header.size_image = image_size;

        std::ofstream out_file(file_path, std::ios::out | std::ios::binary);

        if (!out_file.is_open()) {
            throw std::runtime_error("Error: Cannot open output file!");
        }

        out_file.write(reinterpret_cast<const char*>(&file_header), sizeof(file_header));
        out_file.write(reinterpret_cast<const char*>(&info_header), sizeof(info_header));

        auto pixels = img_data.GetBuffer();
        FlipPixelsHorizontally(pixels, width, height);
        for (int y = height - 1; y >= 0; --y) {
            for (uint32_t x = 0; x < width; ++x) {
                Pixel& pixel = pixels[y * width + x];
                out_file.put(pixel.b);
                out_file.put(pixel.g);
                out_file.put(pixel.r);
            }
            
            for (uint32_t p = 0; p < (4 - (width * 3) % 4) % 4; ++p) {
                out_file.put(0);
            }
        }

        out_file.close();
    }
} // namespace bayer_dithering