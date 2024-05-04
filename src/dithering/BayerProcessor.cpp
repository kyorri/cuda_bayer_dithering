#include "BayerProcessor.h"
#include "FunctionTimer.h"
#include "BayerDithering.h"
#include "BayerResult.h"
#include "BayerResultExporter.h"

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
        BayerResultExporter bayer_exporter;

        if (!std::filesystem::exists(in_directory_)) {
            std::filesystem::create_directory(in_directory_);
        }

        if (!std::filesystem::exists(out_directory_)) {
            std::filesystem::create_directory(out_directory_);
        }

        std::vector<BayerResult> results;
        for (const auto& file : std::filesystem::directory_iterator(in_directory_)) {
            if (file.is_directory()) {
                continue;
            }

            {
                std::filesystem::path file_path = file.path();
                std::string file_name = file_path.stem().string();

                Image img = bmp_reader.ReadBitmapImage(file);
                img.ConvertGrayscale();
                Image s_img = img;
                Image p_img = img;
                
                
                auto start_serial = std::chrono::high_resolution_clock::now();
                bayer_dither.ProcessImageSerial(s_img);
                auto end_serial = std::chrono::high_resolution_clock::now();
                auto duration_serial = std::chrono::duration_cast<std::chrono::microseconds>(end_serial - start_serial);
                BayerResult result(file_name, duration_serial);

                for (int i = 16; i <= 4096; i *= 2) {
                    auto start_parallel = std::chrono::high_resolution_clock::now();
                    bayer_dither.ProcessImageParallel(p_img, i, i);
                    auto end_parallel = std::chrono::high_resolution_clock::now();
                    auto duration_parallel = std::chrono::duration_cast<std::chrono::microseconds>(end_parallel - start_parallel);
                    result.AddParallelTime(duration_parallel, i, i);
                }

                results.push_back(result);

                std::filesystem::path full_file_name(file_name + ".bmp");
                // std::filesystem::path serial_full_file_name(file_name + "_s.bmp");
                // std::filesystem::path parallel_full_file_name(file_name + "_p.bmp");

                bmp_writer.WriteBitmapImage(s_img, out_directory_ / full_file_name);
                // bmp_writer.WriteBitmapImage(s_img, out_directory_ / serial_full_file_name);
                // bmp_writer.WriteBitmapImage(p_img, out_directory_ / parallel_full_file_name);
            }
        };
        bayer_exporter.ExportToCSV(out_directory_ / "results.csv", results);

	};
} // namespace bayer_dithering