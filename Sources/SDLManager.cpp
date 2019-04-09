#include <SDLManager.h>
#include <corecrt_math_defines.h>
#include <Mat4.h>
#include "Vect4.h"

using namespace RasterizerNS;

SDLManager::SDLManager() :
		screenWidth {1024},
		screenHeight {1024},
		input {new Input()}
{
	//Init Everything
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		std::cout << "Video Failed to Initialize" << SDL_GetError() << std::endl;

	//Create Window
	this->window = SDL_CreateWindow("Rasterizer",
				   SDL_WINDOWPOS_UNDEFINED,
		           SDL_WINDOWPOS_UNDEFINED,
		           this->screenWidth,
		           this->screenHeight,
		           SDL_WINDOW_RESIZABLE);

	if (this->window == nullptr)
		std::cout << "Failed to create Window" << SDL_GetError() << std::endl;

	//Create Renderer
	this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_PRESENTVSYNC);

	if (this->renderer == nullptr)
		std::cout << "Failed to Initialize Renderer" << SDL_GetError() << std::endl;

	if(TTF_Init() == -1)
		std::cout << "Unable to Initialize TTF" << SDL_GetError() << std::endl;

	this->font = nullptr;

	this->font = TTF_OpenFont("Dependencies/OpenSans.ttf", 65);

	if (this->font == nullptr)
		std::cout << "Unable to Load font" << std::endl;
}

SDLManager::~SDLManager()
{
	if (this->window != nullptr)
		SDL_DestroyWindow(this->window);

	/*if (this->renderer != nullptr)
		(this->renderer);*/

	if (this->input != nullptr)
		delete this->input;
}


void SDLManager::Draw(Texture *texture)
{

	Color* pixels = texture->getPixels();


	SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
	SDL_RenderClear(this->renderer);

	int width = 0;
	int height = 0;

	for (int i = 0; i <= this->screenHeight * this->screenWidth; ++i)
	{

		if(pixels[i].R() == 0 && pixels[i].G() == 0 && pixels[i].B() == 0)
		{
			++width;

			if (width == this->screenWidth)
			{
				width = 0;
				height += 1;
			}

			continue;
		}
			

		SDL_SetRenderDrawColor(this->renderer, pixels[i].R(), pixels[i].G(), pixels[i].B(), pixels[i].A());
		SDL_RenderDrawPoint(this->renderer, width, height);

		++width;
		
		if (width == this->screenWidth)
		{
			width = 0;
			height += 1;
		}
	}

}

void SDLManager::RenderText(std::string text)
{
	int x = 100;
	int y = 30;

	SDL_Color white = { 255, 255, 255, 255 };

	SDL_Surface *surface = TTF_RenderUTF8_Solid(this->font, text.c_str(), white);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(this->renderer, surface);

	int surface_w, surface_h;
	SDL_QueryTexture(texture, NULL, NULL, &surface_w, &surface_h);

	SDL_Rect rect = { x - surface_h, y, surface_w, surface_h};

	SDL_RenderCopy(this->renderer, texture, NULL, &rect);

	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);

	SDL_RenderPresent(this->renderer);
}

int SDLManager::getWidth() const { return this->screenWidth; }
int SDLManager::getHeight() const { return this->screenHeight; }
Input* SDLManager::GetInput() { return this->input;}
