#include <Rasterizer.h>
#include <iostream>
#include <utility>
#include <algorithm>
#include <limits>
#include <cmath>
#include <corecrt_math_defines.h>

using namespace RasterizerNS;

Rasterizer::Rasterizer(int width, int height): scene(nullptr), texture(nullptr), zBuffer {new float[width * height]}
{
	for (int i = 0; i < width * height; ++i)
		this->zBuffer[i] = FLT_MAX;
}
 
Rasterizer::~Rasterizer()
{
	if (this->zBuffer)
		delete[] this->zBuffer;

	delete scene;
	delete texture;
}

void Rasterizer::RenderScene(Scene* pScene, Texture* pTarget,const Math::Mat4<float>& projectionMatrix)
{
	this->scene = pScene;
	this->texture = pTarget;

	Clear();
	
	std::vector<Vertex> projectedVertices;
	std::vector<Vertex> projectedNormals;
	std::vector<Light> lights = this->scene->GetLights();

	float scalingFactor = 5.f;

	//Rasterize all meshes in the scene
	for (Entity& entity : pScene->GetEntities())
	{
		Mesh* mesh = entity.GetMesh();

		std::vector<Vertex> vertices = mesh->GetVertices();
		std::vector<int> indices = mesh->GetIndices();
		
		//Operation on individual mesh vertex
		for (Vertex v : vertices)
		{	
			Math::Vect4 transformedVertexPosition = projectionMatrix * entity.GetTransform() * Math::Vect4(v.GetPosition());

			//Just Some Normal stuff
			Math::Vect4 transformedNormal(v.GetNormal());
			transformedNormal = entity.GetTransform().Transpose().Inverse() * transformedNormal;

			//Math::Vect3 normalV(transformedNormal.X(), transformedNormal.Y(), transformedNormal.Z());
			Math::Vect3 normalVPlus(transformedVertexPosition.X() + transformedNormal.X(), transformedVertexPosition.Y() + transformedNormal.Y(), transformedVertexPosition.Z() + transformedNormal.Z());

			transformedVertexPosition.Homogenize();

			Vertex vvv(transformedVertexPosition.X(), transformedVertexPosition.Y(), transformedVertexPosition.Z(), v.GetColor(), normalVPlus);

			Color color;	

			for (Light light : lights)
				color += Phong(vvv, light);
			
			float x = transformedVertexPosition.X();
			float y = transformedVertexPosition.Y();
			float z = transformedVertexPosition.Z();

			//Projection
			float px = ((x / 2) + 1) * 0.5f * this->texture->getWidth();
			float py = (this->texture->getHeight() - ((y / 2) + 1) * 0.5f * this->texture->getHeight());
			projectedVertices.emplace_back(px, py, z, color);
		}
	
		//Drawing Triangles
		for (unsigned int i = 0; i < indices.size(); i+= 3)
		{
			DrawTriangleBarycentre(projectedVertices[indices[i]], projectedVertices[indices[i + 1]], projectedVertices[indices[i + 2]]);
		}

		projectedVertices.clear();
		lights.clear();
	}
}

void Rasterizer::Clear()
{
	// Fill Texture with Black
	for (unsigned int y = 0; y < this->texture->getHeight(); ++y)
	{
		for (unsigned int x = 0; x < this->texture->getWidth(); ++x)
		{
			this->texture->SetPixelColor(x, y, Color::Black());
		}
	}
	for (unsigned int i = 0; i < this->texture->getWidth() * this->texture->getHeight(); ++i)
	{
		this->zBuffer[i] = FLT_MAX;	
	}

}

Texture* Rasterizer::getTexture()const { return this->texture; }

void Rasterizer::DrawLine(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2) const
{
	//The Beauty of Bresenham's Algorithm
	float dx = static_cast<float>(x2 - x1);
	float dy = static_cast<float>(y2 - y1);

	if (dy == 0.0f && dx == 0.0f)
	{
		this->texture->SetPixelColor(x1, y1, Color::White());
	}

	else if (abs(dy) > abs(dx))
	{
		if (dy < 0)
		{
			std::swap(x1, x2);
			std::swap(y1, y2);
		}

		const float m = dx / dy;
		unsigned int y = y1;
		unsigned int lastIntY = 0;
		for (unsigned int x = x1; y < y2; ++y, x += m)
		{
			lastIntY = y;
			this->texture->SetPixelColor(x, lastIntY, Color::White());
		}
		if (y2 > lastIntY)
		{
			this->texture->SetPixelColor(x2, y2, Color::White());
		}
	}
	else
	{
		if (dx < 0.0f)
		{
			std::swap(x1, x2);
			std::swap(y1, y2);
		}

		const float m = dy / dx;
		unsigned int x = x1;
		unsigned int lastIntX = 0;
		
		for (unsigned int y = y1; x < x2; ++x, y += m)
		{
			lastIntX = x;
			this->texture->SetPixelColor(lastIntX, y, Color::White());
		}
		if (x2 > lastIntX)
		{
			this->texture->SetPixelColor(x2, y2, Color::White());
		}
	}
}

void Rasterizer::FillBottomFlatTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3) const
{
	float invslope1 = (v2.GetPosition().X() - v1.GetPosition().X()) / (v2.GetPosition().Y() - v1.GetPosition().Y());
	float invslope2 = (v3.GetPosition().X() - v1.GetPosition().X()) / (v3.GetPosition().Y() - v1.GetPosition().Y());

	float curx1 = v1.GetPosition().X();
	float curx2 = v1.GetPosition().X();

	for (float scanlineY = v1.GetPosition().Y(); scanlineY <= v2.GetPosition().Y(); ++scanlineY)
	{
		DrawLine(static_cast<int>(curx1), static_cast<int>(scanlineY), static_cast<int>(curx2), static_cast<int>(scanlineY));
		curx1 += invslope1;
		curx2 += invslope2;
	}
}

void Rasterizer::FillTopFlatTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3) const
{
	float invslope1 = (v3.GetPosition().X() - v1.GetPosition().X()) / (v3.GetPosition().Y() - v1.GetPosition().Y());
	float invslope2 = (v3.GetPosition().X() - v2.GetPosition().X()) / (v3.GetPosition().Y() - v2.GetPosition().Y());

	float curx1 = v3.GetPosition().X();
	float curx2 = v3.GetPosition().X();

	for (float scanlineY = v3.GetPosition().Y(); scanlineY > v1.GetPosition().Y(); --scanlineY)
	{
		DrawLine(static_cast<unsigned int>(curx1), static_cast<unsigned int>(scanlineY), static_cast<unsigned int>(curx2), static_cast<unsigned int>(scanlineY));
		curx1 -= invslope1;
		curx2 -= invslope2;
	}
}

void Rasterizer::DrawTriangleScanLine(Vertex v1, Vertex v2, Vertex v3)
{
	//Sort vertecies by Y coordiante so v1 is the top vertex
	SortVertices(v1, v2, v3);

	if (v2.GetPosition().Y() == v3.GetPosition().Y())		//BotFlat Triangle
	{
		FillBottomFlatTriangle(v1, v2, v3);
	}
		
	else if (v1.GetPosition().Y() == v2.GetPosition().Y())	//TopFlat Triangle
	{
		FillTopFlatTriangle(v1, v2, v3);
	}
		
	else
	{
		//General case
		Vertex v4((v1.GetPosition().X() + (v2.GetPosition().Y() - v1.GetPosition().Y() / (v3.GetPosition().Y() - v1.GetPosition().Y()))  * (v3.GetPosition().X() - v1.GetPosition().X())), v2.GetPosition().Y(), 0, Color::White());

		FillBottomFlatTriangle(v1, v2, v4);
		FillTopFlatTriangle(v2, v4, v3);
	}
}

void Rasterizer::DrawTriangleBarycentre(Vertex v1, Vertex v2, Vertex v3)
{
	const float area = EdgeFunction(v1, v2, v3);

	auto x0 = static_cast<int>(v1.GetPosition().X());
	auto y0 = static_cast<int>(v1.GetPosition().Y());
	auto x1 = static_cast<int>(v2.GetPosition().X());
	auto y1 = static_cast<int>(v2.GetPosition().Y());
	auto x2 = static_cast<int>(v3.GetPosition().X());
	auto y2 = static_cast<int>(v3.GetPosition().Y());

	// Bounding box of triangle
	unsigned int xMin = std::min(std::min(x0, x1), x2);
	unsigned int yMin = std::min(std::min(y0, y1), y2);
	unsigned int xMax = std::max(std::max(x0, x1), x2);
	unsigned int yMax = std::max(std::max(y0, y1), y2);

	// Clip the texture
	xMin = (xMin < 0) ? 0 : xMin;
	yMin = (yMin < 0) ? 0 : yMin;

	xMax = (xMax > this->texture->getWidth()) ? this->texture->getWidth() : xMax;
	yMax = (yMax > this->texture->getHeight()) ? this->texture->getHeight() : yMax;

	// SetColor for pixel in the triangle
	for (unsigned int x = xMin; x <= xMax; ++x)
	{
		for (unsigned int y = yMin; y <= yMax; ++y)
		{
			Vertex vertex(x, y, 0.0f, Color::White());

			float w1 = EdgeFunction(v2, v3, vertex);
			float w2 = EdgeFunction(v3, v1, vertex);
			float w3 = EdgeFunction(v1, v2, vertex);

			if (w1 >= 0 && w2 >= 0 && w3 >= 0)
			{
				w1 /= area;
				w2 /= area;
				w3 /= area;

				float z = 1 / (w1 / v1.GetPosition().Z() + w2 / v2.GetPosition().Z() + w3 / v3.GetPosition().Z());
				
				unsigned char red = w1 * v1.GetColor().R() + w2 * v2.GetColor().R() + w3 * v3.GetColor().R();
				unsigned char green = w1 * v1.GetColor().G() + w2 * v2.GetColor().G() + w3 * v3.GetColor().G();
				unsigned char blue = w1 * v1.GetColor().B() + w2 * v2.GetColor().B() + w3 * v3.GetColor().B();

				int index = y * this->texture->getWidth() + x;

				if (z < this->zBuffer[index])
				{
					this->zBuffer[index] = z;
					this->texture->SetPixelColor(x, y, Color(red, green, blue, 255));
				}
			}
		}
	}
}

float Rasterizer::EdgeFunction(const Vertex& v1, const Vertex& v2, const Vertex& v3)
{
	return ((v3.GetPosition().X() - v1.GetPosition().X()) * (v2.GetPosition().Y() - v1.GetPosition().Y()) - (v3.GetPosition().Y() - v1.GetPosition().Y()) * (v2.GetPosition().X() - v1.GetPosition().X()) );
}

void Rasterizer::SortVertices(Vertex& v1, Vertex& v2, Vertex& v3)
{
	if (v1.GetPosition().Y() > v2.GetPosition().Y())
		std::swap(v1, v2);
		
	if (v1.GetPosition().Y() > v3.GetPosition().Y())
		std::swap(v1, v3);

	if (v2.GetPosition().Y() > v3.GetPosition().Y())
		std::swap(v2, v3);	
}

Color Rasterizer::Phong(Vertex &vertex,Light &light)
{
	int shininess = 5000000;
	Math::Vect3 n = vertex.GetNormal().Normalize();
	Math::Vect3 l = (light.getPosition() - vertex.GetPosition()).Normalize();
	Math::Vect3 r = (n * (n.dotProduct(l) * 2) - l).Normalize();

	float ambient = light.GetAmbientComponent();
	float diffuse = std::clamp(n.dotProduct(l), 0.f, 1.f) * light.GetDiffuseComponent();
	float specular = 0;

	if(l.dotProduct(n) > 0)
	{
		specular = pow(r.dotProduct(vertex.GetPosition()) * (-1), shininess) * light.GetSpecularComponent();
	}

	float phong = diffuse + ambient + specular;

	return Color(static_cast<unsigned char>(vertex.GetColor().R() * phong), static_cast<unsigned char>(vertex.GetColor().G() * phong), static_cast<unsigned char>(vertex.GetColor().B() * phong), 255);

}

Math::Mat4<float> Rasterizer::ProjectionMatrix(float farPlane, float nearPlane, float fov)
{
	Math::Mat4<float> matrix = Math::Mat4<float>::Identity();

	float scale = 1 / (tan((fov / 2) * (M_PI / 180)));

	matrix(0, 0) = scale;
	matrix(1, 1) = scale;
	matrix(2, 2) = - (farPlane / (farPlane - nearPlane));
	matrix(3, 2) = - farPlane * nearPlane / (farPlane - nearPlane);
	matrix(2, 3) = -1;
	matrix(3, 3) = 0;

	return matrix;
}
