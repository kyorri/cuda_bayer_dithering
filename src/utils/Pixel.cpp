#include "Pixel.h"

namespace bayer_dithering {
	Pixel::Pixel() : r(0), g(0), b(0) {}

	Pixel::Pixel(uint8_t grayscale) : r(grayscale / 255.0f), g(grayscale / 255.0f), b(grayscale / 255.0f) {}
	Pixel::Pixel(float grayscale) : r(grayscale), g(grayscale), b(grayscale) {}

	Pixel::Pixel(uint8_t __r, uint8_t __g, uint8_t __b) : r(__r / 255.0f), g(__g / 255.0f), b(__b / 255.0f) {}
	Pixel::Pixel(float __r, float __g, float __b) : r(__r), g(__g), b(__b) {}

	void Pixel::Set(uint8_t grayscale) {
		r = g = b = static_cast<float>(grayscale) / 255.0f;
	}

	void Pixel::Set(float grayscale) {
		r = g = b = grayscale;
	}

	void Pixel::Set(std::tuple<uint8_t, uint8_t, uint8_t> rgb) {
		r = static_cast<float>(std::get<0>(rgb)) / 255.0f;
		g = static_cast<float>(std::get<1>(rgb)) / 255.0f;
		b = static_cast<float>(std::get<2>(rgb)) / 255.0f;
	}

	void Pixel::Set(std::tuple<float, float, float> rgb) {
		r = std::get<0>(rgb);
		g = std::get<1>(rgb);
		b = std::get<2>(rgb);
	}

	void Pixel::ConvertGrayscale() {
		double luminosity = 0.299 * r + 0.587 * g + 0.114 * b;
		r = g = b = (float)luminosity;
	}
}