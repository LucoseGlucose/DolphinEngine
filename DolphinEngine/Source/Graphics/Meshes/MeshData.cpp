#include "MeshData.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <iostream>

MeshData::MeshData(const string& path, int flags)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile("C:/Users/LJorg/source/repos/DolphinEngine/DolphinEngine/Resources/" + path, flags);
	
	if (!scene->HasMeshes())
	{
		importer.FreeScene();
		return;
	}

	aiMesh* mesh = scene->mMeshes[0];
	for (size_t i = 0; i < mesh->mNumVertices; i++)
	{
		vertices.push_back(vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z));
		normals.push_back(vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z));
		uvs.push_back(vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y));
		tangents.push_back(vec3(mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z));
		bitangents.push_back(vec3(mesh->mBitangents[i].x, mesh->mBitangents[i].y, mesh->mBitangents[i].z));
	}

	for (size_t f = 0; f < mesh->mNumFaces; f++)
	{
		const aiFace& face = mesh->mFaces[f];
		for (size_t fi = 0; fi < face.mNumIndices; fi++)
		{
			indices.push_back(face.mIndices[fi]);
		}
	}

	importer.FreeScene();
}

MeshData::MeshData(vector<vec3> vertices, vector<vec3> normals, vector<vec2> uvs,
	vector<unsigned int> indices, vector<vec3> tangents, vector<vec3> bitangents)
{
	this->vertices = vertices;
	this->normals = normals;
	this->uvs = uvs;
	this->indices = indices;
	this->tangents = tangents;
	this->bitangents = bitangents;
}