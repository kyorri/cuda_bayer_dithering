#include "BayerResult.h"

namespace bayer_dithering {
    BayerResult::BayerResult(std::string _image_name, std::chrono::microseconds _serial_time)
        : image_name_(_image_name), serial_time_(_serial_time) {};

    void BayerResult::AddParallelTime(std::chrono::microseconds _time, uint32_t _block_x, uint32_t _block_y) {
        ParallelInfo pi{_time, _block_x, _block_y};
        parallel_times_.push_back(pi);
    };
} // namespace bayer_dithering
