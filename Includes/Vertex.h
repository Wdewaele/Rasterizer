#pragma once

#include <Vect3.h>
#include "Color.h"

namespace Math {
	class Vect3;
}

namespace RasterizerNS
{
	class Vertex
	{
	private:
		Math::Vect3 position;
		Color color;
		Math::Vect3 normal;

	public:
		explicit Vertex(float x, float y, float z, Color color);
		Vertex(Math::Vect3 &p_position, Color color);
		Vertex(float x, float y, float z, Color color, Math::Vect3 normal);
		Vertex();
		
		~Vertex() = default;

		void SetNormal(const Math::Vect3& newNormal);
		void Normalize();
		void setPosition(float x, float y, float z);
		void setColor(Color color);

		const Math::Vect3 GetPosition() const;
		Math::Vect3& GetNormal();
		Color& GetColor();
		Vertex& operator=(const Vertex &other);
	};
}
