#include "Image.h"

Image::Image(const string& path)
{
	stbi_set_flip_vertically_on_load(true);
	data = shared_ptr<unsigned char>(stbi_load(("C:/Users/LJorg/source/repos/DolphinEngine/DolphinEngine/Resources/"
		+ path).c_str(), &width, &height, &numChannels, 4));
}

void Image::SaveAsPNG(const string& path)
{
	stbi_flip_vertically_on_write(true);
	stbi_write_png(path.c_str(), width, height, 4, data.get(), 0);
}

void Image::SaveAsJPG(const string& path, int quality)
{
	stbi_flip_vertically_on_write(true);
	stbi_write_jpg(path.c_str(), width, height, 4, data.get(), quality);
}

void Image::SaveAsTGA(const string& path)
{
	stbi_flip_vertically_on_write(true);
	stbi_write_tga(path.c_str(), width, height, 4, data.get());
}

void Image::SaveAsBMP(const string& path)
{
	stbi_flip_vertically_on_write(true);
	stbi_write_bmp(path.c_str(), width, height, 4, data.get());
}

void Image::SaveAsHDR(const string& path)
{
	stbi_flip_vertically_on_write(true);
	stbi_write_hdr(path.c_str(), width, height, 4, (float*)data.get());
}

vec4 Image::GetPixel(int x, int y)
{
	int pixel = x + y * width;
	return vec4(data.get()[pixel * 4], data.get()[pixel * 4 + 1], data.get()[pixel * 4 + 2], data.get()[pixel * 4 + 3]);
}

vector<vec4> Image::GetPixels(int x, int y, int width, int height)
{
	vector<vec4> pixels = vector<vec4>();

	for (size_t x = 0; x < width; x++)
	{
		for (size_t y = 0; y < height; y++)
		{
			pixels[x + y * width] = GetPixel(x, y);
		}
	}

	return pixels;
}

vector<vec4> Image::GetPixels()
{
	return GetPixels(0, 0, width, height);
}

void Image::SetPixel(vec4 color, int x, int y)
{
	int pixel = x + y * width;

	data.get()[pixel * 4] = color.r;
	data.get()[pixel * 4 + 1] = color.g;
	data.get()[pixel * 4 + 2] = color.g;
	data.get()[pixel * 4 + 3] = color.a;
}

void Image::SetPixels(vector<vec4> colors, int startX, int startY, int width, int height)
{
	for (size_t x = 0; x < width; x++)
	{
		for (size_t y = 0; y < height; y++)
		{
			int xCoord = startX + x;
			int yCoord = startY + y;

			SetPixel(colors[xCoord + yCoord * width], xCoord, yCoord);
		}
	}
}

void Image::SetPixels(vector<vec4> colors)
{
	SetPixels(colors, 0, 0, width, height);
}