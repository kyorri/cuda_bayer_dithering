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

		uint8_t GetR();
		void SetR(uint8_t);

		uint8_t GetG();
		void SetG(uint8_t);

		uint8_t GetB();
		void SetB(uint8_t);

		std::tuple<uint8_t, uint8_t, uint8_t> Get();

		void Set(uint8_t);
		void Set(std::tuple<uint8_t, uint8_t, uint8_t>);

		void ConvertGrayscale();
	private:
		uint8_t r, g, b;
	};
} // namespace bayer_dithering