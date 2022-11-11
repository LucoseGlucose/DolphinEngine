#pragma once

#include <GL/glew.h>

#include "Buffer.h"

class AttribBuffer : public Buffer<float, GL_FLOAT>
{


public:

	AttribBuffer(int bufferType, float* data, int componentSize, int size, int usage = GL_STATIC_DRAW)
		: Buffer<float, GL_FLOAT>(bufferType, data, componentSize, size, usage) {};
};