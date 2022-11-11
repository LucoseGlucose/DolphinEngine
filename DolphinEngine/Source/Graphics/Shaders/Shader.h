#pragma once

#include <string>
#include <map>

using namespace std;

struct Shader
{
	Shader() = delete;

	static inline map<string, int> cachedShaders{  };

	static int Create(const string& path, int shaderType);
};