#include <Entity.h>

using namespace RasterizerNS;

Entity::Entity(): mesh(nullptr), transformation{ Math::Mat4<float>::Identity()} {}

Entity::~Entity()
{
	//if(mesh)
	//	delete mesh;
}

Mesh* Entity::GetMesh()
{
	return this->mesh;
}

Math::Mat4<float> &Entity::GetTransform()
{
	return this->transformation;
}

void Entity::SetMesh(Mesh* p_mesh)
{
	this->mesh = p_mesh;
}

void Entity::SetTransformation(Math::Mat4<float> transform)
{
	this->transformation = transform;
}


