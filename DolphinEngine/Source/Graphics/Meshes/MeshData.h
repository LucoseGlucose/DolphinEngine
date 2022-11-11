#pragma once

#include <string>
#include <vector>
#include <assimp/postprocess.h>

#include "glm/glm.hpp"

using namespace std;
using namespace glm;

struct MeshData
{
	MeshData() = default;
	MeshData(const string& path, int flags = aiProcess_Triangulate | aiProcess_CalcTangentSpace
		| aiProcess_OptimizeMeshes | aiProcess_JoinIdenticalVertices);
	MeshData(vector<vec3> vertices, vector<vec3> normals, vector<vec2> uvs, vector<unsigned int> indices, vector<vec3> tangents, vector<vec3> bitangents);

	vector<vec3> vertices;
	vector<vec3> normals;
	vector<vec2> uvs;
	vector<unsigned int> indices;
	vector<vec3> tangents;
	vector<vec3> bitangents;
};