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
		string sName;

		glGetActiveUniform(id, i, 64, &length, &size, &type, name);
		sName = string(name);
		uniforms.emplace(sName, glGetUniformLocation(id, name));

		if (type == GL_BOOL) boolValues.emplace(sName, GetBool(sName));
		if (type == GL_INT) intValues.emplace(sName, GetInt(sName));
		if (type == GL_FLOAT) floatValues.emplace(sName, GetFloat(sName));
		if (type == GL_FLOAT_VEC2) vec2Values.emplace(sName, GetVec2(sName));
		if (type == GL_FLOAT_VEC3) vec3Values.emplace(sName, GetVec3(sName));
		if (type == GL_FLOAT_VEC4) vec4Values.emplace(sName, GetVec4(sName));
		if (type == GL_FLOAT_MAT3) mat3Values.emplace(sName, GetMat3(sName));
		if (type == GL_FLOAT_MAT4) mat4Values.emplace(sName, GetMat4(sName));

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

void ShaderProgram::Bind()
{
	glUseProgram(id);
}

void ShaderProgram::Unbind()
{
	glUseProgram(0);
}