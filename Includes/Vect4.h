#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include <ostream>
#include <iostream>
#include <Vect3.h>

namespace Math
{
	class Vect3;
	class Vect4
	{
	private:
		float xPos;
		float yPos;
		float zPos;
		float w;

	public:
		explicit Vect4(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.f) :xPos(x), yPos(y), zPos(z), w(w) {}

		explicit Vect4(const Vect3 &vec, float _w = 1.f) : xPos{ vec.X() }, yPos{ vec.Y() }, zPos{ vec.Z() }, w{ _w } {}

		~Vect4() = default;

		Vect4(const Vect4& other)
		{
			this->xPos = other.xPos;
			this->yPos = other.yPos;
			this->zPos = other.zPos;
			this->w = other.W();
		}

		/*--------*/

		void Homogenize()
		{
			if (w != 0)
			{
				this->xPos /= w;
				this->yPos /= w;
				this->zPos /= w;
				this->w = 1;
			}
		}

		void Normalize()
		{
			float magnitude = this->GetMagnitude();

			this->xPos = this->xPos / magnitude;
			this->yPos = this->yPos / magnitude;
			this->zPos = this->zPos / magnitude;
			this->w = this->w / magnitude;
		}

		/*----surcharge----*/

		Vect4& operator+(const Vect4 &other)
		{
			this->xPos += other.xPos;
			this->yPos += other.yPos;
			this->zPos += other.zPos;
			this->w	   += other.w;

			return *this;
		}

		Vect4& operator*(const Vect4 &other)
		{
			this->xPos += other.xPos;
			this->yPos += other.yPos;
			this->zPos += other.zPos;
			this->w *= other.w;

			return *this;
		}

		Vect4 operator+(const Vect4 &other) const
		{
			Vect4 TempVect(this->xPos + other.xPos, this->yPos + other.yPos, this->zPos + other.zPos, this->w + other.W());
			return TempVect;
		}

		Vect4 &operator*(float scalar)
		{
			this->xPos *= scalar;
			this->yPos *= scalar;
			this->zPos *= scalar;
			this->w *= scalar;

			return *this;
		}

		Vect4& operator=(const Vect4 &other)
		{
			this->xPos = other.xPos;
			this->yPos = other.xPos;
			this->zPos = other.xPos;
			this->w = other.w;

			return *this;
		}

		/*--------*/

		float GetMagnitude() const
		{
			float NumberReturned = 0;

			NumberReturned = sqrt((this->xPos * this->xPos) +
								 (this->yPos * this->yPos) +
								 (this->zPos * this->zPos) + 
								 (this->w * this->w));
			return NumberReturned;
		}



		friend std::ostream &operator<<(std::ostream &os, const Vect4 &v)
		{
			os << v.X() << "-" << v.Y() << "-" << v.Z() << "-" << v.W();
			return os;
		}

		float X() const { return this->xPos; }
		float Y() const { return this->yPos; }
		float Z() const { return this->zPos; }
		float W() const { return this->w; }
		void X(float x) { this->xPos = x; }
		void Y(float y) { this->yPos = y; }
		void Z(float z) { this->zPos = z; }
		void W(float w) { this->w = w; }

	};
}
