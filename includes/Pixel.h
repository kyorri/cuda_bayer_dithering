#pragma once

#include <tuple>
#include <cstdint>

namespace bayer_dithering {
	class Pixel {
	public:
		Pixel();
		Pixel(uint8_t);
		Pixel(uint8_t, uint8_t, uint8_t);
		~Pixel() = default;

		Pixel& operator=(const Pixel&) = default;
		Pixel(const Pixel&) = default;

		Pixel& operator=(Pixel&&) = default;
		Pixel(Pixel&&) = default;

		void Set(uint8_t);
		void Set(std::tuple<uint8_t, uint8_t, uint8_t>);

		void ConvertGrayscale();

		uint8_t r, g, b;
	};
} // namespace bayer_dithering