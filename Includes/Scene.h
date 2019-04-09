#pragma once

#include <vector>
#include "Entity.h"
#include "Light.h"

namespace RasterizerNS
{
	class Scene
	{
	private:
		std::vector<Entity> entities;
		std::vector<Light> lights;

	public:
		Scene();
		~Scene();

		std::vector<Entity> &GetEntities();
		std::vector<Light> &GetLights();
	};
}
