#include <Vertex.h>
#include <iostream>

using namespace RasterizerNS;

Vertex::Vertex(Math::Vect3 &p_position, Color color)
	: position{p_position}, color {color}, normal {position} {}

Vertex::Vertex(float x, float y, float z, Color color, Math::Vect3 normal)
	:position {Math::Vect3(x, y, z)}, color(color), normal(normal) {}

Vertex::Vertex()
{
	this->position.X(0);
	this->position.Y(0);
	this->position.Z(0);
}

Vertex::Vertex(float x, float y, float z, Color color)
	: position{ Math::Vect3(x, y, z) }, color{color} {}

const Math::Vect3 Vertex::GetPosition() const
{
	return this->position;
}
Color& Vertex::GetColor()
{
	return this->color;
}

Math::Vect3& Vertex::GetNormal()
{
	return this->normal;
}

void Vertex::SetNormal(const Math::Vect3& newNormal)
{
	this->normal = newNormal;
}

void Vertex::Normalize()
{
	this->normal.Normalize();
}

Vertex& Vertex::operator=(const Vertex& other)
{
	this->position = other.position;
	return *this;
}

void Vertex::setPosition(float x, float y, float z)
{
	this->position = Math::Vect3(x, y, z);
}

void Vertex::setColor(Color color)
{
	this->color = color;
}
