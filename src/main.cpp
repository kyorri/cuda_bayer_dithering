#include <iostream>
#include <chrono>
#include <filesystem>


#include "BayerDithering.h"
#include "BitmapWriter.h"
#include "BitmapReader.h"

void OutputImage(bayer_dithering::Image&, std::filesystem::path);

int main (int argc, char** argv) {
    std::string image_name = "galaxy";
    auto in_image_path = std::filesystem::current_path().append("in").append(image_name + ".bmp");
    auto out_image_path = std::filesystem::current_path().append("out").append(image_name + ".bmp");

    std::cout << in_image_path << std::endl;
    std::cout << out_image_path << std::endl;
    
    // bayer_dithering::NetpbmReader test{std::filesystem::path(in_image_path)};
    // bayer_dithering::Image read_image = test.Read();

    bayer_dithering::BayerDithering bd;
    bayer_dithering::BitmapReader bmp_reader;
    bayer_dithering::Image image = bmp_reader.ReadBitmapImage(in_image_path);
    auto start = std::chrono::system_clock::now();
    bd.ProcessImageSerial(image);
    auto end = std::chrono::system_clock::now();

    bayer_dithering::BitmapWriter bmp_writer;
    bmp_writer.WriteBitmapImage(image, out_image_path);

    auto time_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "This image took " << time_elapsed.count() << " milliseconds to be processed!" << std::endl;
    return 0;
}
