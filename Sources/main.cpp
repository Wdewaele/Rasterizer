#include <iostream>
#include <SDLManager.h>
#include <Mat4.h>
#include "Rasterizer.h"
#include <string>

using namespace RasterizerNS;

int main(int argc, char* argv[])
{
	SDLManager sdlManager;
	Scene scene;

	Light light(Math::Vect3(3, 0, -2), 0.4f, 0.4f, 0.6f);
	scene.GetLights().push_back(light);

	//Cube1 Red
	Mesh* cube1 = Mesh::CreateCube();
	Entity cubeEntity1;	
	cubeEntity1.SetMesh(cube1);
	scene.GetEntities().push_back(cubeEntity1);

	//Sphere Yellow
	/*Mesh* sphere = Mesh::CreateSphere(16, 16);
	Entity sphereEntity;
	sphereEntity.SetMesh(sphere);
	scene.GetEntities().push_back(sphereEntity);*/

	//Rasterizer 
	Texture texture(sdlManager.getWidth(), sdlManager.getHeight());
	Rasterizer rasterizer(sdlManager.getWidth(), sdlManager.getHeight());

	scene.GetEntities()[0].SetTransformation(sdlManager.GetInput()->getTransformationMatrix());
	//scene.GetEntities()[1].SetTransformation(sdlManager.GetInput()->getTransformationMatrix());

	int start;
	int currentTime;
	

	while(sdlManager.GetInput()->getInputState() != InputState::EXIT)
	{
		start = SDL_GetTicks();
		
		if(sdlManager.GetInput()->getSelector() == 0)
			scene.GetEntities()[0].SetTransformation(sdlManager.GetInput()->getTransformationMatrix());
			
		rasterizer.RenderScene(&scene, &texture, sdlManager.GetInput()->getProjectionMode());
		sdlManager.GetInput()->InputListen();
		sdlManager.Draw(&texture);

		currentTime = 1000 / (SDL_GetTicks() - start);
		sdlManager.RenderText("FPS: " + std::to_string(currentTime));
	}

	return 0;
}