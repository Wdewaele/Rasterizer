#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include <ostream>

namespace Math
{
	
	class Vect3
	{
	private:
		float xPos;
		float yPos;
		float zPos;

	public:
		explicit Vect3(float x = 0, float y = 0, float z = 0) : xPos{ x }, yPos{ y }, zPos{ z } {}
		Vect3(const Vect3& other) : xPos{ other.xPos }, yPos{ other.yPos }, zPos{ other.zPos } {}

		~Vect3() {}

		float GetMagnitude() const
		{
			return sqrt((this->xPos * this->xPos) + (this->yPos * this->yPos) + (this->zPos * this->zPos));
		}

		Vect3& Normalize()
		{
			float magnitude = GetMagnitude();
			this->xPos = this->xPos / magnitude;
			this->yPos = this->yPos / magnitude;
			this->zPos = this->zPos / magnitude;
			return *this;
		}

		/*--------- surcharge ---------*/

		Vect3& operator-(const Vect3& Other)
		{
			this->xPos -= Other.xPos;
			this->yPos -= Other.yPos;
			this->zPos -= Other.zPos;

			return *this;
		}

		Vect3& operator+(const Vect3& Other)
		{
			this->xPos += Other.xPos;
			this->yPos += Other.yPos;
			this->zPos += Other.zPos;

			return *this;
		}

		Vect3 &operator*(const float scalar)
		{
			this->xPos *= scalar;
			this->yPos *= scalar;
			this->zPos *= scalar;

			return *this;
		}

		float dotProduct(const Vect3 &other) const
		{
			return (this->X() * other.X() + this->Y() * other.Y() + this->Z() * other.Z());
		}

		Vect3 &operator=(const Vect3 &Other)
		{
			this->xPos = Other.xPos;
			this->yPos = Other.yPos;
			this->zPos = Other.zPos;
			return *this;
		}

		float X() const { return this->xPos; }
		float Y() const { return this->yPos; }
		float Z() const { return this->zPos; }
		void X(float x) { this->xPos = x; }
		void Y(float y) { this->yPos = y; }
		void Z(float z) { this->zPos = z; }

		friend std::ostream &operator<<(std::ostream &os, const Vect3 &v)
		{
			os << v.xPos << " / " << v.yPos << " / " << v.zPos;
			return os;
		}
	};
}
