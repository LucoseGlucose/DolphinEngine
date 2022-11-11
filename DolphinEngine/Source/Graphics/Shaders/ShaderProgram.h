#pragma once

#include <GL/glew.h>
#include <vector>
#include <string>
#include <map>

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Texture.h"

using namespace std;
using namespace glm;

class ShaderProgram
{


public:

	ShaderProgram(vector<string> paths, vector<int> shaderTypes);
	~ShaderProgram();

	unsigned int id;
	map<string, int> uniforms;

	vector<Texture*> textures;

	inline void SetBool(string name, bool val)
	{
		glUseProgram(id);
		glUniform1i(uniforms[name], val);
	}
	inline bool GetBool(string name)
	{
		glUseProgram(id);
		int i;
		glGetUniformiv(id, uniforms[name], &i);
		return i;
	}
	inline void SetInt(string name, int val)
	{
		glUseProgram(id);
		glUniform1i(uniforms[name], val);
	}
	inline int GetInt(string name)
	{
		glUseProgram(id);
		int i;
		glGetUniformiv(id, uniforms[name], &i);
		return i;
	}
	inline void SetFloat(string name, float val)
	{
		glUseProgram(id);
		glUniform1f(uniforms[name], val);
	}
	inline float GetFloat(string name)
	{
		glUseProgram(id);
		float i;
		glGetUniformfv(id, uniforms[name], &i);
		return i;
	}
	inline void SetVec2(string name, vec2 val)
	{
		glUseProgram(id);
		glUniform2f(uniforms[name], val.x, val.y);
	}
	inline vec2 GetVec2(string name)
	{
		glUseProgram(id);
		float* i = new float[2];
		glGetUniformfv(id, uniforms[name], i);
		vec2 v = vec2(i[0], i[1]);
		delete[] i;
		return v;
	}
	inline void SetVec3(string name, vec3 val)
	{
		glUseProgram(id);
		glUniform3f(uniforms[name], val.x, val.y, val.z);
	}
	inline vec3 GetVec3(string name)
	{
		glUseProgram(id);
		float* i = new float[3];
		glGetUniformfv(id, uniforms[name], i);
		vec3 v = vec3(i[0], i[1], i[2]);
		delete[] i;
		return v;
	}
	inline void SetVec4(string name, vec4 val)
	{
		glUseProgram(id);
		glUniform4f(uniforms[name], val.x, val.y, val.z, val.w);
	}
	inline vec4 GetVec4(string name)
	{
		glUseProgram(id);
		float* i = new float[4];
		glGetUniformfv(id, uniforms[name], i);
		vec4 v = vec4(i[0], i[1], i[2], i[3]);
		delete[] i;
		return v;
	}
	inline void SetMat3(string name, mat3 val)
	{
		glUseProgram(id);
		glUniformMatrix3fv(uniforms[name], 1, false, glm::value_ptr(val));
	}
	inline mat3 GetMat3(string name)
	{
		glUseProgram(id);
		float* i = new float[9];
		glGetUniformfv(id, uniforms[name], i);
		mat3 m = mat3(i[0], i[1], i[2], i[3], i[4], i[5], i[6], i[7], i[8]);
		delete[] i;
		return m;
	}
	inline void SetMat4(string name, mat4 val)
	{
		glUseProgram(id);
		glUniformMatrix4fv(uniforms[name], 1, false, glm::value_ptr(val));
	}
	inline mat4 GetMat4(string name)
	{
		glUseProgram(id);
		float* i = new float[16];
		glGetUniformfv(id, uniforms[name], i);
		mat4 m = mat4(i[0], i[1], i[2], i[3], i[4], i[5], i[6], i[7], i[8], i[9], i[10], i[11], i[12], i[13], i[14], i[15]);
		delete[] i;
		return m;
	}
};