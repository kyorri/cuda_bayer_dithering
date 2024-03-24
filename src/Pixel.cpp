#include "Pixel.h"

namespace bayer_dithering {
	Pixel::Pixel() : r(0), g(0), b(0) {};

	Pixel::Pixel(uint8_t grayscale) : r(grayscale), g(grayscale), b(grayscale) {};

	Pixel::Pixel(uint8_t __r, uint8_t __g, uint8_t __b) : r(__r), g(__g), b(__b) {};

	uint8_t Pixel::GetR() {
		return r;
	};
	void Pixel::SetR(uint8_t __r) {
		r = __r;
	}

	uint8_t Pixel::GetG() {
		return g;
	};
	void Pixel::SetG(uint8_t __g) {
		g = __g;
	};

	uint8_t Pixel::GetB() {
		return b;
	};
	void Pixel::SetB(uint8_t __b) {
		b = __b;
	};

	std::tuple<uint8_t, uint8_t, uint8_t> Pixel::Get() {
		return { r, g, b };
	};

	void Pixel::Set(uint8_t grayscale) {
		r = g = b = static_cast<uint32_t>(grayscale);
	};

	void Pixel::Set(std::tuple<uint8_t, uint8_t, uint8_t> rgb) {
		r = static_cast<uint32_t>(std::get<0>(rgb));
		g = static_cast<uint32_t>(std::get<1>(rgb));
		b = static_cast<uint32_t>(std::get<2>(rgb));
	};

	void Pixel::ConvertGrayscale() {
		double luminosity = 0.299 * r + 0.587 * g + 0.114 * b;
		r = g = b = static_cast<uint8_t>(luminosity);
	};
}