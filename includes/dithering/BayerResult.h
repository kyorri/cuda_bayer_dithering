#pragma once

#include <vector>
#include <chrono>
#include <string>
#include <cstdint>
#include <filesystem>

namespace bayer_dithering {
    struct ParallelInfo {
        std::chrono::microseconds parallel_time_;
        uint32_t block_x_, block_y_;
        friend class BayerResultExporter;
    };

    class BayerResult {
    public:
        BayerResult(std::string, std::chrono::microseconds);
        void AddParallelTime(std::chrono::microseconds, uint32_t, uint32_t);
    private:
        std::string image_name_;
        std::chrono::microseconds serial_time_;
        std::vector<ParallelInfo> parallel_times_;
        friend class BayerResultExporter;
    };
} // namespace bayer_dithering
