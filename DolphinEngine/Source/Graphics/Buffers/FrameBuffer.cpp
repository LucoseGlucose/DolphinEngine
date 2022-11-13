#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(vector<Texture*> textures, vector<RenderBuffer*> renderBuffers, vector<int> attachTypes)
{
	this->textures = textures;
	this->renderBuffers = renderBuffers;
	this->attachTypes = attachTypes;

	for (size_t i = 0; i < attachTypes.size(); i++)
	{
		int diff = attachTypes[i] - GL_COLOR_ATTACHMENT0;
		if (diff <= 0 && diff > -16) drawBuffers.push_back(attachTypes[i]);
	}

	glGenFramebuffers(1, &id);
	glBindFramebuffer(GL_FRAMEBUFFER, id);

	for (size_t i = 0; i < textures.size(); i++)
	{
		glFramebufferTexture2D(GL_FRAMEBUFFER, attachTypes[i], textures[i]->textureType, textures[i]->id, 0);
	}

	for (size_t i = 0; i < renderBuffers.size(); i++)
	{
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachTypes[i + textures.size()], GL_RENDERBUFFER, renderBuffers[i]->id);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

FrameBuffer::~FrameBuffer()
{
	for (size_t i = 0; i < textures.size(); i++)
	{
		delete textures[i];
	}

	for (size_t i = 0; i < renderBuffers.size(); i++)
	{
		delete renderBuffers[i];
	}
}