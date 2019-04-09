#pragma once
#include "Mesh.h"
#include "Mat4.h"

namespace RasterizerNS
{
	class Entity
	{
	private:
		Mesh* mesh;
		Math::Mat4<float> transformation;

	public:
		Entity();
		~Entity();

		Mesh* GetMesh();
		Math::Mat4<float>& GetTransform();

		void SetMesh(Mesh* p_mesh);
		void SetTransformation( Math::Mat4<float> transform);
	};
}
