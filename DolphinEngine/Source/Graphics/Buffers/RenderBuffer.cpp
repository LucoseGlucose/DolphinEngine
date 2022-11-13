#include "RenderBuffer.h"

RenderBuffer::RenderBuffer(int format, int width, int height)
{
	this->format = format;

	glGenRenderbuffers(1, &id);
	glBindRenderbuffer(GL_RENDERBUFFER, id);
	glRenderbufferStorage(GL_RENDERBUFFER, format, width, height);
}

RenderBuffer::~RenderBuffer()
{
	glDeleteRenderbuffers(1, &id);
}