#include <iostream>
#include <fstream>
#include <chrono>
#include <filesystem>


#include "BayerDithering.h"
#include "BitmapWriter.h"
#include "BitmapReader.h"

void OutputImage(bayer_dithering::Image&, std::filesystem::path);

int main (int argc, char** argv) {

    std::filesystem::path abs_path = std::filesystem::current_path();

    std::filesystem::path log_file_path = std::filesystem::current_path().append("log_file.txt");
    std::ofstream log_file(log_file_path);

    std::string image_name = "galaxy";
    auto in_image_path = std::filesystem::current_path().append("in").append(image_name + ".bmp");
    auto out_s_image_path = std::filesystem::current_path().append("out").append(image_name + "_s.bmp");
    auto out_p_image_path = std::filesystem::current_path().append("out").append(image_name + "_p.bmp");

    bayer_dithering::BitmapReader bmp_reader;
    bayer_dithering::Image image = bmp_reader.ReadBitmapImage(in_image_path);

    bayer_dithering::Image s_image = image;
    bayer_dithering::Image p_image = image;
    std::cout << "Images were loaded! Now starting to process the Bayer Dithering!" << std::endl;
    log_file << "Images were loaded! Now starting to process the Bayer Dithering!" << std::endl;

    bayer_dithering::BayerDithering bayer_dithering;

    auto s_start = std::chrono::system_clock::now();
    bayer_dithering.ProcessImageSerial(s_image);
    auto s_end = std::chrono::system_clock::now();
    auto s_time_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(s_end - s_start);
    std::cout << "This image took " << s_time_elapsed.count() << " milliseconds to be processed on a single core!" << std::endl;
    log_file << "This image took " << s_time_elapsed.count() << " milliseconds to be processed on a single core!" << std::endl;


    for (int i = 1; i <= 1024; i*=2) {
        auto p_start = std::chrono::system_clock::now();
        bayer_dithering.ProcessImageParallel(p_image, i, i);
        auto p_end = std::chrono::system_clock::now();
        auto p_time_elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(p_end - p_start);
        std::cout << "This image took " << p_time_elapsed.count() << " milliseconds to be processed parallel using CUDA! (" << i << "*" << i << ")" << std::endl;
        log_file << "This image took " << p_time_elapsed.count() << " milliseconds to be processed parallel using CUDA! (" << i << "*" << i << ")" << std::endl;
    }

    std::cout << "Writing to output files!" << std::endl;
    log_file << "Writing to output files!" << std::endl;
    
    bayer_dithering::BitmapWriter bmp_writer;
    bmp_writer.WriteBitmapImage(s_image, out_s_image_path);
    bmp_writer.WriteBitmapImage(p_image, out_p_image_path);
    
    return 0;
}
