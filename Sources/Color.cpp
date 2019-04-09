#include <Color.h>

using namespace RasterizerNS;

Color::Color() : r{ 0 }, g{ 0 }, b{ 0 }, a{255} {}

Color::Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
	: r{ red }, g{ green }, b{ blue }, a{alpha} {}


Color& Color::operator+=(const Color& other)
{
	this->r = other.r;
	this->g = other.g;
	this->b = other.b;
	this->a = other.a;

	return *this;
}

unsigned char &Color::R() { return this->r; }
unsigned char &Color::G() { return this->g; }
unsigned char &Color::B() { return this->b; }
unsigned char &Color::A() { return this->a; }

void Color::A(unsigned char value)
{
	this->a = value;
}

void Color::R(unsigned char value)
{
	this->r = value;
}

void Color::G(unsigned char value)
{
	this->g = value;
}

void Color::B(unsigned char value)
{
	this->b = value;
}

unsigned char Color::R() const { return this->r; }
unsigned char Color::G() const { return this->g; }
unsigned char Color::B() const { return this->b; }
unsigned char Color::A() const { return this->a; }



Color Color::White() { return Color(255, 255, 255, 255); }
Color Color::Black() { return Color(0, 0, 0, 255); }
Color Color::Red()   { return Color(255, 0, 0, 255); }
Color Color::Green() { return Color(0, 255, 0, 255); }
Color Color::Blue()  { return Color(0, 0, 255, 255); }
Color Color::Yellow() { return Color(255, 255, 0, 255); }
