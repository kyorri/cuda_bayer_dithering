#include "BitmapWriter.h"

namespace bayer_dithering {

    void BitmapWriter::WriteBitmapImage(Image& img_data, std::filesystem::path file_path) {
        uint32_t width = img_data.GetWidth();
        uint32_t height = img_data.GetHeight();

        std::ofstream out_file;
        out_file.open(file_path, std::ios::out | std::ios::binary);

        if (!out_file.is_open()) {
            throw std::runtime_error("Error: File could not be opened!");
        }

        uint8_t bmp_padding[3] = { 0x00, 0x00, 0x00 };
        const uint32_t padding = ((4 - (width * 3) % 4) % 4);

        const uint32_t file_header_size = 14;
        const uint32_t info_header_size = 40;
        const uint32_t bmp_file_size = file_header_size + info_header_size + width * height * 3 + padding * height;

        uint8_t file_header[file_header_size] = {};

        file_header[0] = 'B';
        file_header[1] = 'M';
        file_header[2] = bmp_file_size;
        file_header[3] = bmp_file_size >> 8;
        file_header[4] = bmp_file_size >> 16;
        file_header[5] = bmp_file_size >> 24;

        file_header[6];
        file_header[7];

        file_header[8];
        file_header[9];

        file_header[10] = file_header_size + info_header_size;
        file_header[11];
        file_header[12];
        file_header[13];

        uint8_t info_header[info_header_size] = {};

        info_header[0] = info_header_size;
        info_header[1];
        info_header[2];
        info_header[3];

        info_header[4] = width;
        info_header[5] = width >> 8;
        info_header[6] = width >> 16;
        info_header[7] = width >> 24;

        info_header[8] = height;
        info_header[9] = height >> 8;
        info_header[10] = height >> 16;
        info_header[11] = height >> 24;

        info_header[12] = 1;
        info_header[13];

        info_header[14] = 24;
        info_header[15];

        info_header[16];
        info_header[17];
        info_header[18];
        info_header[19];

        info_header[20];
        info_header[21];
        info_header[22];
        info_header[23];

        info_header[24];
        info_header[25];
        info_header[26];
        info_header[27];

        info_header[28];
        info_header[29];
        info_header[30];
        info_header[31];

        info_header[32];
        info_header[33];
        info_header[34];
        info_header[35];
        
        info_header[36];
        info_header[37];
        info_header[38];
        info_header[39];

        out_file.write(reinterpret_cast<char*>(file_header), file_header_size);
        out_file.write(reinterpret_cast<char*>(info_header), info_header_size);

        for (uint32_t y = 0; y < height; y++) {
            for (uint32_t x = 0; x < width; x++) {
                Pixel& p = img_data.GetPixel(x, y);

                uint8_t r = static_cast<uint8_t>(p.r * 255.0f);
                uint8_t g = static_cast<uint8_t>(p.g * 255.0f);
                uint8_t b = static_cast<uint8_t>(p.b * 255.0f);

                uint8_t pixel_repr[] = { b, g, r };
                out_file.write(reinterpret_cast<char*>(pixel_repr), 3);
            }
            out_file.write(reinterpret_cast<char*>(bmp_padding), padding);
        }

        out_file.close();
    }
} // namespace bayer_dithering