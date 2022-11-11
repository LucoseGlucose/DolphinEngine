#include "Shader.h"

#include <GL/glew.h>
#include <fstream>
#include <sstream>

int Shader::Create(const string& path, int shaderType)
{
	if (cachedShaders.contains(path)) return cachedShaders[path];

	int id = glCreateShader(shaderType);

	ifstream stream;
	stream.open("C:/Users/LJorg/source/repos/DolphinEngine/DolphinEngine/Shaders/" + path);

	stringstream output;
	output << stream.rdbuf();
	stream.close();

	string text = output.str();
	const char* source = text.c_str();

	glShaderSource(id, 1, &source, nullptr);
	glCompileShader(id);

	return id;
}