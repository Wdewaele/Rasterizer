#ifndef _INPUT_H
#define _INPUT_H

#include <SDL.h>
#include "Mat4.h"

namespace RasterizerNS
{
	enum class InputState
	{
		IDLE,
		EXIT
	};

	class Input
	{
	private:
		InputState inputState;
		Math::Mat4<float>* projectionMatrix;
		Math::Mat4<float> transformationMatrix;

		Math::Mat4<float> perspectiveProjection;
		Math::Mat4<float> orthographicProjection;

		float x;
		float y;
		float z;
		float anglex;
		float angley;

		float offset;

		int selector;

	public:
		Input();
		~Input();
		void InputListen();
		void ResetInput();
		InputState getInputState() const;

		Math::Mat4<float>& getProjectionMode();
		Math::Mat4<float>& getTransformationMatrix();
		int getSelector();

	};
}

#endif