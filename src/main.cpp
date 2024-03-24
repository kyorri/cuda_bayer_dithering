#include <iostream>
#include <chrono>
#include <filesystem>

#include <cuda.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include "NetpbmReader.h"
#include "BayerDithering.h"

void OutputImage(bayer_dithering::Image&, std::filesystem::path);

int main (int argc, char** argv) {
    auto in_image_path = std::filesystem::current_path().append("sunflower.pnm");
    auto out_image_path = std::filesystem::current_path().append("out_buffer.pnm");

    std::cout << in_image_path << std::endl;
    
    bayer_dithering::NetpbmReader test{std::filesystem::path(in_image_path)};
    bayer_dithering::Image read_image = test.Read();

    bayer_dithering::BayerDithering bd;

    auto start = std::chrono::system_clock::now();
    bd.ProcessImage(read_image);
    auto end = std::chrono::system_clock::now();

    OutputImage(read_image, out_image_path);
    auto time_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "This image took " << time_elapsed.count() << " milliseconds to be processed!" << std::endl;
    return 0;
}

void OutputImage(bayer_dithering::Image& img, std::filesystem::path image_path) {
    std::ofstream fout(image_path);
    fout << "P1" << std::endl << img.GetWidth() << " " << img.GetHeight() << std::endl;

    std::stringstream out_buffer;
    for (bayer_dithering::Pixel& pixel : img.GetBuffer()) {
        (std::get<0>(pixel.Get()) == 255) ? out_buffer << "0 " : out_buffer << "1 "; 
    }
    fout << out_buffer.rdbuf();
}