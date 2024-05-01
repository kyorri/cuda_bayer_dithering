#pragma once

#include <tuple>
#include <cstdint>

namespace bayer_dithering {
	class Pixel {
	public:
		Pixel();
		Pixel(uint8_t);
		Pixel(float);
		Pixel(uint8_t, uint8_t, uint8_t);
		Pixel(float, float, float);
		~Pixel() = default;

		Pixel& operator=(const Pixel&) = default;
		Pixel(const Pixel&) = default;

		Pixel& operator=(Pixel&&) = default;
		Pixel(Pixel&&) = default;

		void Set(uint8_t);
		void Set(float);
		void Set(std::tuple<uint8_t, uint8_t, uint8_t>);
		void Set(std::tuple<float, float, float>);

		void ConvertGrayscale();

		float r, g, b;
	};
} // namespace bayer_dithering