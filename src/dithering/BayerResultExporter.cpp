#include "BayerResultExporter.h"

#include <fstream>

namespace bayer_dithering {
    void BayerResultExporter::ExportToCSV(std::filesystem::path _export_path, std::vector<BayerResult> _results) {
        std::ofstream csv(_export_path, std::ios::out);

        csv << "image name;s_time(ms);";
        int i;
        for (i = 16; i < 4096; i *= 2) {
            csv << "p_time(ms) " << i << "*" << i << ";";
        }
        csv << "p_time(ms) " << i << "*" << i << ";" << std::endl;

        for (auto& result : _results) {
            csv << result.image_name_ << ";" << result.serial_time_.count() / 1'000.0 << ";";
            for (auto& parallel_time : result.parallel_times_) {
                csv << parallel_time.parallel_time_.count() / 1'000.0 << ";";
            }
            csv << std::endl;
        }
    };
} // namespace bayer_dithering
