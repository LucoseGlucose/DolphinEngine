#include "Mesh.h"

Mesh::Mesh(MeshData meshData)
{
	this->meshData = meshData;
	this->vertexArray = new VertexArray(meshData);
}

Mesh::Mesh(MeshData meshData, VertexArray* vertexArray)
{
	this->meshData = meshData;
	this->vertexArray = vertexArray;
}

Mesh::~Mesh()
{
	delete vertexArray;
}