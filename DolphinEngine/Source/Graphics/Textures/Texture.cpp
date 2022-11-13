#include "Texture.h"

Texture::Texture(vector<int> widths, vector<int> heights, vector<shared_ptr<unsigned char>> data,
	int textureType, int internalFormat, int format, int filter, int wrapping)
{
	this->widths = widths;
	this->heights = heights;
	this->format = format;
	this->data = data;
	this->textureType = textureType;
	this->internalFormat = internalFormat;

	glGenTextures(1, &id);
	glBindTexture(textureType, id);

	glTexParameteri(textureType, GL_TEXTURE_WRAP_S, wrapping);
	glTexParameteri(textureType, GL_TEXTURE_WRAP_T, wrapping);
	glTexParameteri(textureType, GL_TEXTURE_WRAP_R, wrapping);
	glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, filter);

	for (size_t i = 0; i < widths.size(); i++)
	{
		glTexImage2D(textureType, 0, internalFormat, widths[i], heights[i], 0, format, GL_UNSIGNED_BYTE, data[i].get());
	}
	glGenerateMipmap(textureType);
}

Texture::Texture(vector<Image*> images, int textureType, int filter, int wrapping)
{
	this->format = GL_RGBA;
	this->textureType = textureType;
	this->internalFormat = GL_RGBA8;

	glGenTextures(1, &id);
	glBindTexture(textureType, id);

	glTexParameteri(textureType, GL_TEXTURE_WRAP_S, wrapping);
	glTexParameteri(textureType, GL_TEXTURE_WRAP_T, wrapping);
	glTexParameteri(textureType, GL_TEXTURE_WRAP_R, wrapping);
	glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, filter);

	for (size_t i = 0; i < images.size(); i++)
	{
		widths.push_back(images[i]->width);
		heights.push_back(images[i]->height);
		glTexImage2D(textureType, 0, internalFormat, widths[i], heights[i], 0, format, GL_UNSIGNED_BYTE, images[i]->data.get());
	}
	glGenerateMipmap(textureType);
}

Texture::Texture(vector<int> widths, vector<int> heights, vector<shared_ptr<unsigned char>> data,
	int textureType, vector<int> bindingTypes, int internalFormat, int format, int filter, int wrapping)
{
	this->widths = widths;
	this->heights = heights;
	this->format = format;
	this->data = data;
	this->textureType = textureType;
	this->internalFormat = internalFormat;

	glGenTextures(1, &id);
	glBindTexture(textureType, id);

	glTexParameteri(textureType, GL_TEXTURE_WRAP_S, wrapping);
	glTexParameteri(textureType, GL_TEXTURE_WRAP_T, wrapping);
	glTexParameteri(textureType, GL_TEXTURE_WRAP_R, wrapping);
	glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, filter);

	for (size_t i = 0; i < widths.size(); i++)
	{
		glTexImage2D(bindingTypes[i], 0, internalFormat, widths[i], heights[i], 0, format, GL_UNSIGNED_BYTE, data[i].get());
	}
	glGenerateMipmap(textureType);
}

Texture::Texture(vector<Image*> images, int textureType, vector<int> bindingTypes, int filter, int wrapping)
{
	this->format = GL_RGBA;
	this->textureType = textureType;
	this->internalFormat = GL_RGBA8;

	glGenTextures(1, &id);
	glBindTexture(textureType, id);

	glTexParameteri(textureType, GL_TEXTURE_WRAP_S, wrapping);
	glTexParameteri(textureType, GL_TEXTURE_WRAP_T, wrapping);
	glTexParameteri(textureType, GL_TEXTURE_WRAP_R, wrapping);
	glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, filter);

	for (size_t i = 0; i < images.size(); i++)
	{
		widths.push_back(images[i]->width);
		heights.push_back(images[i]->height);
		glTexImage2D(bindingTypes[i], 0, internalFormat, widths[i], heights[i], 0, format, GL_UNSIGNED_BYTE, images[i]->data.get());
	}
	glGenerateMipmap(textureType);
}

Texture::Texture(int width, int height, shared_ptr<unsigned char> data, int textureType, int internalFormat, int format, int filter, int wrapping)
{
	this->widths = vector<int>{ width };
	this->heights = vector<int>{ height };
	this->format = format;
	this->data = vector<shared_ptr<unsigned char>>{ data };
	this->textureType = textureType;
	this->internalFormat = internalFormat;

	glGenTextures(1, &id);
	glBindTexture(textureType, id);

	glTexParameteri(textureType, GL_TEXTURE_WRAP_S, wrapping);
	glTexParameteri(textureType, GL_TEXTURE_WRAP_T, wrapping);
	glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, filter);

	glTexImage2D(textureType, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data.get());
	glGenerateMipmap(textureType);
}

Texture::Texture(Image* image, int textureType, int filter, int wrapping)
{
	this->format = GL_RGBA;
	this->textureType = textureType;
	this->widths = vector<int>{ image->width };
	this->heights = vector<int>{ image->height };
	this->internalFormat = GL_RGBA8;

	glGenTextures(1, &id);
	glBindTexture(textureType, id);

	glTexParameteri(textureType, GL_TEXTURE_WRAP_S, wrapping);
	glTexParameteri(textureType, GL_TEXTURE_WRAP_T, wrapping);
	glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, filter);

	glTexImage2D(textureType, 0, format, image->width, image->height, 0, format, GL_UNSIGNED_BYTE, image->data.get());
	glGenerateMipmap(textureType);
}

Texture::~Texture()
{
	glDeleteTextures(1, &id);
}

void Texture::Bind(int slot)
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(textureType, id);
}

void Texture::Unbind(int slot)
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(textureType, 0);
}