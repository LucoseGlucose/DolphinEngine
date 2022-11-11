#pragma once

#include "MeshData.h"
#include "VertexArray.h"

class Mesh
{


public:

	Mesh(MeshData meshData);
	Mesh(MeshData meshData, VertexArray* vertexArray);
	~Mesh();

	MeshData meshData;
	VertexArray* vertexArray;
};