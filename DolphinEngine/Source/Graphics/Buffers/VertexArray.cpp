#include "VertexArray.h"
#include "Utils.h"

VertexArray::VertexArray(const MeshData& meshData)
{
	attribBuffers = vector<AttribBuffer*>
	{
		new AttribBuffer(GL_ARRAY_BUFFER, Expand(meshData.vertices).data(), 3, meshData.vertices.size() * 3),
			new AttribBuffer(GL_ARRAY_BUFFER, Expand(meshData.normals).data(), 3, meshData.vertices.size() * 3),
			new AttribBuffer(GL_ARRAY_BUFFER, Expand(meshData.uvs).data(), 2, meshData.vertices.size() * 2),
			new AttribBuffer(GL_ARRAY_BUFFER, Expand(meshData.tangents).data(), 3, meshData.vertices.size() * 3),
			new AttribBuffer(GL_ARRAY_BUFFER, Expand(meshData.bitangents).data(), 3, meshData.vertices.size() * 3),
	};
	indexBuffer = new IndexBuffer(GL_ELEMENT_ARRAY_BUFFER, meshData.indices.data(), 1, meshData.indices.size());

	glGenVertexArrays(1, &id);
	glBindVertexArray(id);

	for (size_t i = 0; i < attribBuffers.size(); i++)
	{
		glEnableVertexAttribArray(i);
		glBindBuffer(attribBuffers[i]->bufferType, attribBuffers[i]->id);
		glVertexAttribPointer(i, attribBuffers[i]->componentSize, attribBuffers[i]->dataType, false, 0, 0);
	}

	glBindVertexArray(0);
}

VertexArray::VertexArray(vector<AttribBuffer*> attribBuffers, IndexBuffer* indexBuffer)
{
	this->attribBuffers = attribBuffers;
	this->indexBuffer = indexBuffer;

	glGenVertexArrays(1, &id);
	glBindVertexArray(id);

	for (size_t i = 0; i < attribBuffers.size(); i++)
	{
		glEnableVertexAttribArray(i);
		glBindBuffer(attribBuffers[i]->bufferType, attribBuffers[i]->id);
		glVertexAttribPointer(i, attribBuffers[i]->componentSize, attribBuffers[i]->dataType, false, 0, 0);
	}

	glBindVertexArray(0);
}