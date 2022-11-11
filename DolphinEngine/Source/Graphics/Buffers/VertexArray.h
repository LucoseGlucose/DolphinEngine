#pragma once

#include <GL/glew.h>
#include <vector>

#include "AttribBuffer.h"
#include "IndexBuffer.h"
#include "MeshData.h"

using namespace std;

class VertexArray
{


public:

	VertexArray(const MeshData& meshData);
	VertexArray(vector<AttribBuffer*> buffers, IndexBuffer* indexBuffer);

	unsigned int id;
	vector<AttribBuffer*> attribBuffers;
	IndexBuffer* indexBuffer;
};