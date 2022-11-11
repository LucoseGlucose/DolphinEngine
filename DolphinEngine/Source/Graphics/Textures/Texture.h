#pragma once

#include <GL/glew.h>
#include <vector>
#include <memory>

#include "Image.h"

using namespace std;

class Texture
{


public:

	Texture(vector<int> widths, vector<int> heights, vector<shared_ptr<unsigned char>> data, int textureType,
		int format = GL_RGBA, int filter = GL_LINEAR, int wrapping = GL_CLAMP_TO_EDGE);
	Texture(vector<Image*> images, int textureType, int filter = GL_LINEAR, int wrapping = GL_CLAMP_TO_EDGE);
	Texture(vector<int> widths, vector<int> heights, vector<shared_ptr<unsigned char>> data, int textureType, vector<int> bindingTypes,
		int format = GL_RGBA, int filter = GL_LINEAR, int wrapping = GL_CLAMP_TO_EDGE);
	Texture(vector<Image*> images, int textureType, vector<int> bindingTypes, int filter = GL_LINEAR, int wrapping = GL_CLAMP_TO_EDGE);
	~Texture();

	unsigned int id;
	vector<int> widths;
	vector<int> heights;
	int textureType;
	int format;
	vector<shared_ptr<unsigned char>> data;
};