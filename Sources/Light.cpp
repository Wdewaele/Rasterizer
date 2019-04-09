#include <Light.h>

using namespace RasterizerNS;

Light::Light(const Math::Vect3& position, float ambient, float diffuse, float specular):
	ambientComponent {ambient},
	diffuseComponent {diffuse},
	specularComponent {specular},
	position {position}
{
}

Light::Light(const Light& other)
{
	this->position = other.position;
	this->ambientComponent = other.ambientComponent;
	this->diffuseComponent = other.diffuseComponent;
	this->specularComponent = other.specularComponent;
}

Math::Vect3& Light::getPosition() { return this->position; }

float& Light::GetAmbientComponent()  { return this->ambientComponent; }

float& Light::GetDiffuseComponent()  { return this->diffuseComponent; }

float& Light::GetSpecularComponent() { return this->specularComponent; }
