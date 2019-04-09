#include <Scene.h>
#include <iostream>

using namespace RasterizerNS;

Scene::Scene()
{
	std::cout << "Scene Created" << std::endl;
}

Scene::~Scene()
{
	this->entities.clear();
	this->lights.clear();
	std::cout << "Scene Deleted" << std::endl;
}

std::vector<Entity> &Scene::GetEntities()  { return this->entities; }

std::vector<Light>& Scene::GetLights() { return this->lights; }
