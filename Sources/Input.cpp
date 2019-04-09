#include <Input.h>
#include <iostream>
#include "Rasterizer.h"

using namespace RasterizerNS;

Input::Input() : 
	inputState {InputState::IDLE},
	perspectiveProjection { Rasterizer::ProjectionMatrix(5, 1, 45)},
	orthographicProjection {Math::Mat4<float>::Identity()},
	projectionMatrix {&perspectiveProjection},
	transformationMatrix {Math::Mat4<float>::CreateTransformationMatrix(Math::Vect3(0, 0, 0), Math::Vect3(0, 0, -3), Math::Vect3(1, 1, 1))},
	x {0},
	y {0},
	z {-3},
	anglex {0},
	angley {0},
	offset {0.3f},
	selector {0}
{
}

Input::~Input()
{	
}

void Input::InputListen()
{
	SDL_Event event;

	while(SDL_PollEvent(&event))
	{
		if(event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				this->inputState = InputState::EXIT;
				break;
			case SDLK_p:
				this->projectionMatrix = &this->perspectiveProjection;
				break;

			case SDLK_o:
				this->projectionMatrix = &this->orthographicProjection;
				break;

			case SDLK_x:
				this->x -= this->offset;
				break;

			case SDLK_c:
				this->x += this->offset;
				break;

			case SDLK_y:
				this->y += this->offset;
				break;

			case SDLK_h:
				this->y -= this->offset;
				break;

			case SDLK_z:
				this->z += this->offset;
				break;

			case SDLK_a:
				this->z -= this->offset;
				break;

			case SDLK_1:
				this->selector = 0;
				break;

			case SDLK_2:
				this->selector = 1;
				break;

			case SDLK_b:
				this->anglex += this->offset * 10;
				break;

			case SDLK_v:
				this->angley += this->offset * 10;
				break;

			}
			this->transformationMatrix = Math::Mat4<float>::CreateTransformationMatrix(Math::Vect3(this->anglex, this->angley, 0), Math::Vect3(this->x, this->y, this->z), Math::Vect3(1, 1, 1));
		}		
	}
}

void Input::ResetInput()
{
	this->inputState = InputState::IDLE;
}

InputState Input::getInputState() const
{
	return this->inputState;
}

Math::Mat4<float>& Input::getProjectionMode()
{
	return *this->projectionMatrix;
}

Math::Mat4<float>& Input::getTransformationMatrix()
{
	return this->transformationMatrix;
}

int Input::getSelector()
{
	return this->selector;
}
