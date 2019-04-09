#ifndef _DISPLAY_H
#define _DISPLAY_H

#include <cassert>
#include <iostream>
#include <list>
#include <SDL.h>
#include "Input.h"
#include "Rasterizer.h"
#include <SDL_ttf.h>

namespace RasterizerNS
{
	class SDLManager
	{
	private:
		int screenWidth;
		int screenHeight;
		SDL_Window* window;
		SDL_Renderer* renderer;
		Input* input;
		Texture* texture;
		TTF_Font *font;
		

	public:
		SDLManager();
		~SDLManager();
		void Draw(Texture *texture);
		void RenderText(std::string text);

		int getWidth() const;
		int getHeight() const;
		Input* GetInput();

	};
}

#endif