#pragma once

#include <GL/glew.h>

#include "Buffer.h"

class IndexBuffer : public Buffer<const unsigned int, GL_UNSIGNED_INT>
{


public:

	IndexBuffer(int bufferType, const unsigned int* data, int componentSize, int size, int usage = GL_STATIC_DRAW)
		: Buffer<const unsigned int, GL_UNSIGNED_INT>(bufferType, data, componentSize, size, usage) {};
};