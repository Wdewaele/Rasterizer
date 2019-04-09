#pragma once
#include <vector>
#include "Vertex.h"

namespace RasterizerNS
{
	class Mesh
	{
	private:
		std::vector<Vertex> vertices;
		std::vector<int> indices;

	public:
		explicit Mesh() = default;
		Mesh(std::vector<Vertex> meshVertices, std::vector<int> meshIndices);
		~Mesh();

		std::vector<Vertex>& GetVertices();
		std::vector<int>& GetIndices();

		void addVertex(const Vertex& v);
		void SetNormals();

		static Mesh* CreateCube();
		static Mesh* CreateTriangle();

		static Mesh* CreateCube2();
		static Mesh* CreateSphere(int latitudeCount, int longitudeCount);
	};
}
