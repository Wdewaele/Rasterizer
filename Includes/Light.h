#pragma once
#include "Vect3.h"

namespace RasterizerNS
{
	class Light
	{
	private:
		float ambientComponent;
		float diffuseComponent;
		float specularComponent;

		Math::Vect3 position;

	public:
		explicit Light(const Math::Vect3& position, float ambient, float diffuse, float specular);
		Light(const Light& other);
		~Light() = default;

		Math::Vect3& getPosition();
		float& GetAmbientComponent();
		float& GetDiffuseComponent();
		float& GetSpecularComponent();
		
	};
}
