#include <Texture.h>
#include <iostream>

using namespace RasterizerNS;

Texture::Texture(unsigned p_width, unsigned p_height)
	: width{ p_width }, height{ p_height }
{
	int textureSize = width * height;

	std::cout << "Texture Created" << std::endl;
	this->pixels = new Color[textureSize];

	for (int i = 0; i < textureSize; ++i)
		this->pixels[i] = Color::Black();
}

Texture::~Texture()
{
	delete this->pixels;
}

void Texture::SetPixelColor(unsigned x, unsigned y, const Color& c)
{
	if (x < 0 || x > this->getWidth()-1 || y < 0 || y > this->getHeight()-1)
		return;

	this->pixels[(y == 0 ? x : y * this->getWidth() + x)] = c;
}

unsigned int &Texture::getWidth()  { return this->width; }
unsigned int &Texture::getHeight() { return this->height; }
Color* Texture::getPixels() const { return this->pixels; }
