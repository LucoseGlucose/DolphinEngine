#pragma once

#include <GL/glew.h>

template<typename T, int DataType>
class Buffer
{


public:

	Buffer(int bufferType, T* data, int componentSize, int size, int usage = GL_STATIC_DRAW);
	~Buffer();

	void SetData(T* data);
	void SetData(T* data, int offset, int length);

	unsigned int id;
	int bufferType;
	T* data;
	int dataType = DataType;
	int size;
	int componentSize;
};

template<typename T, int DataType>
Buffer<T, DataType>::Buffer(int bufferType, T* data, int componentSize, int size, int usage)
{
	this->bufferType = bufferType;
	this->data = data;
	this->size = size;
	this->componentSize = componentSize;

	glGenBuffers(1, &id);
	glBindBuffer(bufferType, id);
	glBufferData(bufferType, size * sizeof(T), data, usage);

	glBindBuffer(bufferType, 0);
}

template<typename T, int DataType>
Buffer<T, DataType>::~Buffer()
{
	glDeleteBuffers(1, &id);
	delete data;
}

template<typename T, int DataType>
void Buffer<T, DataType>::SetData(T* data)
{
	SetData(data, 0, size * sizeof(T));
}

template<typename T, int DataType>
void Buffer<T, DataType>::SetData(T* data, int offset, int length)
{
	glBindBuffer(bufferType, id);
	glBufferSubData(bufferType, offset, length, data);
	glBindBuffer(bufferType, 0);
}