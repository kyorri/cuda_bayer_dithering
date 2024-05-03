#pragma once

#include "BayerResult.h"

#include <vector>

namespace bayer_dithering {
    class BayerResultExporter{
        public:
            void ExportToCSV(std::filesystem::path, std::vector<BayerResult>);
    };
} // namespace bayer_dithering
