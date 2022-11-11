#include "ShaderProgram.h"
#include "Shader.h"

ShaderProgram::ShaderProgram(vector<string> paths, vector<int> shaderTypes)
{
	id = glCreateProgram();

	for (size_t i = 0; i < paths.size(); i++)
	{
		glAttachShader(id, Shader::Create(paths[i], shaderTypes[i]));
	}
	glLinkProgram(id);

	int uniformCount;
	glGetProgramiv(id, GL_ACTIVE_UNIFORMS, &uniformCount);

	for (size_t i = 0; i < uniformCount; i++)
	{
		int length;
		int size;
		unsigned int type;
		char* name = new char[64];

		glGetActiveUniform(id, i, 64, &length, &size, &type, name);
		uniforms.emplace(string(name), glGetUniformLocation(id, name));

		delete[] name;
	}
}

ShaderProgram::~ShaderProgram()
{
	for (size_t i = 0; i < textures.size(); i++)
	{
		glDeleteTextures(1, &textures[i]->id);
	}
	glDeleteProgram(id);
}