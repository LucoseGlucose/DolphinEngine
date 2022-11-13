#pragma once

#include <GL/glew.h>

#include "App.h"

class RenderBuffer
{


public:

	RenderBuffer(int format, int width, int height);
	~RenderBuffer();

	unsigned int id;
	int format;
};