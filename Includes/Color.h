#pragma once

namespace RasterizerNS
{
	class Color
	{
	private:
		unsigned char r;
		unsigned char g;
		unsigned char b;
		unsigned char a;

	public:
		explicit Color();
		Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);
		~Color() = default;

		Color& operator+=(const Color &other);

		static Color White();
		static Color Black();
		static Color Red();
		static Color Green();
		static Color Blue();
		static Color Yellow();

		unsigned char &R();
		unsigned char &G();
		unsigned char &B();
		unsigned char &A();

		void A(unsigned char value);
		void R(unsigned char value);
		void G(unsigned char value);
		void B(unsigned char value);

		unsigned char R() const;
		unsigned char G() const;
		unsigned char B() const;
		unsigned char A() const;

	};
}