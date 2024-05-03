#pragma once

#include <chrono>

namespace bayer_dithering {
    template<typename Func, typename... Args>
    class FunctionTimer {
    public:
        FunctionTimer(Func _function, Args&&... _arguments) {
            auto start = std::chrono::high_resolution_clock::now();
            _function(std::forward<Args>(_arguments)...);
            auto end = std::chrono::high_resolution_clock::now();
            time_ = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        }

        std::chrono::microseconds GetTime() const {
            return time_;
        }

    private:
        std::chrono::microseconds time_;
    };
} // namespace bayer_dithering
