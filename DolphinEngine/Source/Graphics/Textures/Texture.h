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
		int internalFormat = GL_RGBA8, int format = GL_RGBA, int filter = GL_LINEAR, int wrapping = GL_CLAMP_TO_EDGE);
	Texture(vector<Image*> images, int textureType, int filter = GL_LINEAR, int wrapping = GL_CLAMP_TO_EDGE);

	Texture(vector<int> widths, vector<int> heights, vector<shared_ptr<unsigned char>> data, int textureType, vector<int> bindingTypes,
		int internalFormat = GL_RGBA8, int format = GL_RGBA, int filter = GL_LINEAR, int wrapping = GL_CLAMP_TO_EDGE);
	Texture(vector<Image*> images, int textureType, vector<int> bindingTypes, int filter = GL_LINEAR, int wrapping = GL_CLAMP_TO_EDGE);

	Texture(int width, int height, shared_ptr<unsigned char> data, int textureType,
		int internalFormat = GL_RGBA8, int format = GL_RGBA, int filter = GL_LINEAR, int wrapping = GL_CLAMP_TO_EDGE);
	Texture(Image* image, int textureType, int filter = GL_LINEAR, int wrapping = GL_CLAMP_TO_EDGE);

	~Texture();

	void Bind(int slot);
	void Unbind(int slot);

	unsigned int id;
	vector<int> widths;
	vector<int> heights;
	int textureType;
	int internalFormat;
	int format;
	vector<shared_ptr<unsigned char>> data;
};