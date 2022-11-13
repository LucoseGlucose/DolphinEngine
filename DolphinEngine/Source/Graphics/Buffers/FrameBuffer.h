#pragma once

#include <GL/glew.h>
#include <vector>

#include "Texture.h"
#include "RenderBuffer.h"

using namespace std;

class FrameBuffer
{


public:

	FrameBuffer(vector<Texture*> textures, vector<RenderBuffer*> renderBuffers, vector<int> attachTypes);
	~FrameBuffer();

	unsigned int id;
	vector<Texture*> textures;
	vector<RenderBuffer*> renderBuffers;
	vector<int> attachTypes;
	vector<unsigned int> drawBuffers;
};