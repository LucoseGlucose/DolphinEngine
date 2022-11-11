#pragma once

#include <string>
#include <vector>
#include <memory>

#include "stb/stb_image.h"
#include "stb/stb_image_write.h"

#include "glm/glm.hpp"

using namespace std;
using namespace glm;

class Image
{


public:

	Image(const string& path);

	void SaveAsPNG(const string& path);
	void SaveAsJPG(const string& path, int quality = 100);
	void SaveAsTGA(const string& path);
	void SaveAsBMP(const string& path);
	void SaveAsHDR(const string& path);

	vec4 GetPixel(int x, int y);
	vector<vec4> GetPixels(int x, int y, int width, int height);
	vector<vec4> GetPixels();

	void SetPixel(vec4 color, int x, int y);
	void SetPixels(vector<vec4> colors, int startX, int startY, int width, int height);
	void SetPixels(vector<vec4> colors);

	int width;
	int height;
	int numChannels;
	shared_ptr<unsigned char> data;
};