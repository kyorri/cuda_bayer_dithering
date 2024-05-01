#include "BayerProcessor.h"

int main () {
    {
        bayer_dithering::BayerProcessor bayer_processor;
        bayer_processor.ProcessImages();
    }
    return 0;
}
