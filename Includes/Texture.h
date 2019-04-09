#pragma once
#include "Color.h"

namespace RasterizerNS
{
	class Texture
	{
	private:
		unsigned int width;
		unsigned int height;
		Color* pixels;

	public:
		explicit Texture(unsigned int p_width, unsigned int p_height);
		~Texture();

		void SetPixelColor(unsigned int x, unsigned int y, const Color& c);
		unsigned int &getWidth();
		unsigned int &getHeight();
		Color* getPixels() const;
	};
}
