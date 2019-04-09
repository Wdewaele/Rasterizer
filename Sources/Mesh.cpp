#define _USE_MATH_DEFINES
#include <cmath>

#include <Mesh.h>
#include <iostream>
#include <utility>


using namespace RasterizerNS;


Mesh::Mesh(std::vector<Vertex> meshVertices, std::vector<int> meshIndices)
	: vertices{std::move(meshVertices)}, indices{std::move(meshIndices)}
{}

Mesh::~Mesh()
{
	vertices.clear();
	indices.clear();
}

std::vector<Vertex> &Mesh::GetVertices()  { return this->vertices; }
std::vector<int> &Mesh::GetIndices() { return this->indices; }


void Mesh::addVertex(const Vertex& v)
{
	this->vertices.push_back(v);
}

void Mesh::SetNormals()
{
	for (auto& vertex : this->vertices)
	{
		Math::Vect3 temp = vertex.GetPosition();
		vertex.SetNormal(temp.Normalize());
	}
}

Mesh* Mesh::CreateCube()
{
	Mesh* mesh = new Mesh();

	mesh->vertices.reserve(8);
	mesh->vertices.emplace_back(-0.5, -0.5, 0.5, Color::Red());
	mesh->vertices.emplace_back(0.5, -0.5, 0.5, Color::Red());
	mesh->vertices.emplace_back(0.5, 0.5, 0.5, Color::Red());
	mesh->vertices.emplace_back(-0.5, 0.5, 0.5, Color::Red());
	mesh->vertices.emplace_back(-0.5, -0.5, -0.5, Color::Red());
	mesh->vertices.emplace_back(0.5, -0.5, -0.5, Color::Red());
	mesh->vertices.emplace_back(0.5, 0.5, -0.5, Color::Red());
	mesh->vertices.emplace_back(-0.5, 0.5, -0.5, Color::Red());

	mesh->indices.reserve(36);
	mesh->indices.push_back(0);
	mesh->indices.push_back(1);
	mesh->indices.push_back(2);

	mesh->indices.push_back(2);
	mesh->indices.push_back(3);
	mesh->indices.push_back(0);

	mesh->indices.push_back(1);
	mesh->indices.push_back(5);
	mesh->indices.push_back(6);

	mesh->indices.push_back(6);
	mesh->indices.push_back(2);
	mesh->indices.push_back(1);

	mesh->indices.push_back(7);
	mesh->indices.push_back(6);
	mesh->indices.push_back(5);


	mesh->indices.push_back(5);
	mesh->indices.push_back(4);
	mesh->indices.push_back(7);

	mesh->indices.push_back(4);
	mesh->indices.push_back(0);
	mesh->indices.push_back(3);

	mesh->indices.push_back(3);
	mesh->indices.push_back(7);
	mesh->indices.push_back(4);

	mesh->indices.push_back(4);
	mesh->indices.push_back(5);
	mesh->indices.push_back(1);

	mesh->indices.push_back(1);
	mesh->indices.push_back(0);
	mesh->indices.push_back(4);

	mesh->indices.push_back(3);
	mesh->indices.push_back(2);
	mesh->indices.push_back(6);

	mesh->indices.push_back(6);
	mesh->indices.push_back(7);
	mesh->indices.push_back(3);
	

	if (mesh)
		std::cout << "Cube Created" << std::endl;
	else
		std::cout << "Problem Creating Cube" << std::endl;

	mesh->SetNormals();

	return mesh;
}

Mesh* Mesh::CreateTriangle()
{
	Mesh* mesh = new Mesh();

	mesh->vertices.reserve(3);
	mesh->vertices.emplace_back(-0.5, -0.5, 0, Color::Red());
	mesh->vertices.emplace_back(0.5, -0.5, 0, Color::Green());
	mesh->vertices.emplace_back(0, 0.5, 0, Color::Blue());

	mesh->indices.reserve(3);
	mesh->indices.push_back(0);
	mesh->indices.push_back(1);
	mesh->indices.push_back(2);
	
	if (mesh)
		std::cout << "Triangle Created" << std::endl;
	else
		std::cout << "Problem Creating Triangle" << std::endl;

	mesh->SetNormals();

	return mesh;
}

Mesh* Mesh::CreateCube2()
{
	Mesh* mesh = new Mesh();

	mesh->vertices.reserve(8);
	mesh->vertices.emplace_back(-0.5, -0.5, 0.5, Color::Yellow());
	mesh->vertices.emplace_back(0.5, -0.5, 0.5, Color::Yellow());
	mesh->vertices.emplace_back(0.5, 0.5, 0.5, Color::Yellow());
	mesh->vertices.emplace_back(-0.5, 0.5, 0.5, Color::Yellow());
	mesh->vertices.emplace_back(-0.5, -0.5, -0.5, Color::Blue());
	mesh->vertices.emplace_back(0.5, -0.5, -0.5, Color::Blue());
	mesh->vertices.emplace_back(0.5, 0.5, -0.5, Color::Blue());
	mesh->vertices.emplace_back(-0.5, 0.5, -0.5, Color::Blue());

	mesh->indices.reserve(36);
	mesh->indices.push_back(0);
	mesh->indices.push_back(1);
	mesh->indices.push_back(2);

	mesh->indices.push_back(2);
	mesh->indices.push_back(3);
	mesh->indices.push_back(0);

	mesh->indices.push_back(1);
	mesh->indices.push_back(5);
	mesh->indices.push_back(6);

	mesh->indices.push_back(6);
	mesh->indices.push_back(2);
	mesh->indices.push_back(1);

	mesh->indices.push_back(7);
	mesh->indices.push_back(6);
	mesh->indices.push_back(5);


	mesh->indices.push_back(5);
	mesh->indices.push_back(4);
	mesh->indices.push_back(7);

	mesh->indices.push_back(4);
	mesh->indices.push_back(0);
	mesh->indices.push_back(3);

	mesh->indices.push_back(3);
	mesh->indices.push_back(7);
	mesh->indices.push_back(4);

	mesh->indices.push_back(4);
	mesh->indices.push_back(5);
	mesh->indices.push_back(1);

	mesh->indices.push_back(1);
	mesh->indices.push_back(0);
	mesh->indices.push_back(4);

	mesh->indices.push_back(3);
	mesh->indices.push_back(2);
	mesh->indices.push_back(6);

	mesh->indices.push_back(6);
	mesh->indices.push_back(7);
	mesh->indices.push_back(3);

	if (mesh)
		std::cout << "Cube Created" << std::endl;
	else
		std::cout << "Problem Creating Cube" << std::endl;

	mesh->SetNormals();

	return mesh;
}

Mesh* Mesh::CreateSphere(int latitudeCount, int longitudeCount)
{
	Mesh* sphere = new Mesh();

	sphere->vertices.reserve(latitudeCount * longitudeCount);
	sphere->indices.reserve(latitudeCount * longitudeCount * 2);

	double radius = 0.5f;

	for (double latNumber = 0; latNumber <= latitudeCount; latNumber++) {
		double theta = latNumber * M_PI / latitudeCount;
		double sinTheta = sin(theta);
		double cosTheta = cos(theta);

		for (double longNumber = 0; longNumber <= longitudeCount; longNumber++) {

			double phi = longNumber * 2 * M_PI / longitudeCount;
			double sinPhi = sin(phi);
			double cosPhi = cos(phi);

			float x = (float)(cosPhi * sinTheta);
			float z = (float)(sinPhi * sinTheta);

			sphere->vertices.emplace_back(x * radius, cosTheta * radius, z * radius, Color::Yellow());
			sphere->vertices.back().SetNormal(Math::Vect3(x, cosTheta, z));
		}
	}
	for (int latNumber2 = 0; latNumber2 < latitudeCount; latNumber2++) {
		for (int longNumber = 0; longNumber < longitudeCount; longNumber++) {

			int first = (latNumber2 * (longitudeCount + 1)) + longNumber;
			int second = first + longitudeCount + 1;

			sphere->indices.emplace_back(first);
			sphere->indices.emplace_back(second);
			sphere->indices.emplace_back(first + 1);
			
			sphere->indices.emplace_back(second);
			sphere->indices.emplace_back(second + 1);
			sphere->indices.emplace_back(first + 1);
		}
	}

	sphere->SetNormals();

	return sphere;
}
