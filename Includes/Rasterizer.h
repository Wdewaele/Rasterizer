#pragma once
#include "Scene.h"
#include "Texture.h"

namespace RasterizerNS
{
	class Rasterizer
	{
	private:
		Scene* scene;		//Not the Owner
		Texture* texture;	//Not the Owner
		float* zBuffer;

	public:
		explicit Rasterizer(int width, int height);
		~Rasterizer();

		void RenderScene(Scene* pScene, Texture* pTarget,const Math::Mat4<float>& projectionMatrix);
		void Clear();

		Texture* getTexture() const;

		void DrawLine(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2) const;
		void FillBottomFlatTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3) const;
		void FillTopFlatTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3) const;
		void DrawTriangleScanLine(Vertex v1, Vertex v2, Vertex v3);
		void DrawTriangleBarycentre(Vertex v1, Vertex v2, Vertex v3);
		float EdgeFunction(const Vertex& v1, const Vertex& v2, const Vertex& v3);
		void SortVertices(Vertex& v1, Vertex& v2, Vertex& v3);

		Color Phong(Vertex &vertex, Light &light);

		static Math::Mat4<float> ProjectionMatrix(float farPlane, float nearPlane, float fov);
	};
}
