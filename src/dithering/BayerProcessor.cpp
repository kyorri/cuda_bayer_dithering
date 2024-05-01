#include "BayerProcessor.h"

#include <algorithm>

namespace bayer_dithering {

    BayerProcessor::BayerProcessor()
        : in_directory_(std::filesystem::current_path().append("in")), out_directory_(std::filesystem::current_path().append("out")) {};

	BayerProcessor::BayerProcessor(std::filesystem::path _in, std::filesystem::path _out) 
        : in_directory_(_in), out_directory_(_out) {};


	void BayerProcessor::ProcessImages() 
    {
        BitmapReader bmp_reader;
        BitmapWriter bmp_writer;
        BayerDithering bayer_dither;

        if (!std::filesystem::exists(in_directory_)) {
            std::filesystem::create_directory(in_directory_);
        }

        if (!std::filesystem::exists(out_directory_)) {
            std::filesystem::create_directory(out_directory_);
        }
        
        for (const auto& file : std::filesystem::directory_iterator(in_directory_)) {
            if (file.is_directory()) {
                continue;
            }

            {
                std::filesystem::path file_path = file.path();
                std::string file_name = file_path.stem().string();

                Image img = bmp_reader.ReadBitmapImage(file);
                Image s_img = img;
                Image p_img = img;

                bayer_dither.ProcessImageSerial(s_img);
                bayer_dither.ProcessImageParallel(p_img, 1024, 1024);

                std::filesystem::path serial_full_file_name(file_name + "_s.bmp");
                std::filesystem::path parallel_full_file_name(file_name + "_p.bmp");

                bmp_writer.WriteBitmapImage(s_img, out_directory_ / serial_full_file_name);
                bmp_writer.WriteBitmapImage(p_img, out_directory_ / parallel_full_file_name);
            }
        };

	};
} // namespace bayer_dithering