#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <optional>

#include "Rendering.h"
#include "MeshComponent.h"
#include "SceneObject.h"
#include "Component.h"
#include "App.h"
#include "Texture.h"

using namespace std;

void Rendering::Init()
{
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(DebugMessage, nullptr);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LEQUAL);

	if (outputCam == nullptr)
	{
		optional<CameraComponent*> cam = App::scene->FindComponent<CameraComponent>();

		if (cam.has_value()) outputCam = cam.value();
		else outputCam = App::scene->CreateObject("Output Camera")->AddComponent<CameraComponent>();
	}

	if (skybox == nullptr)
	{
		skybox = new Texture(vector<Image*>{ new Image("Images/Skybox/front.jpg"), new Image("Images/Skybox/right.jpg"),
			new Image("Images/Skybox/back.jpg"), new Image("Images/Skybox/left.jpg"), new Image("Images/Skybox/top.jpg"),
			new Image("Images/Skybox/bottom.jpg")}, GL_TEXTURE_CUBE_MAP, vector<int>{ GL_TEXTURE_CUBE_MAP_POSITIVE_Z, GL_TEXTURE_CUBE_MAP_POSITIVE_X,
			GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, GL_TEXTURE_CUBE_MAP_NEGATIVE_X, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, GL_TEXTURE_CUBE_MAP_POSITIVE_Y });
	}

	if (skyboxShader == nullptr)
	{
		skyboxShader = new ShaderProgram(vector<string>{ "SkyboxVert.glsl", "SkyboxFrag.glsl" }, vector<int>{ GL_VERTEX_SHADER, GL_FRAGMENT_SHADER });
	}

	if (skyboxMesh == nullptr)
	{
		skyboxMesh = new Mesh(MeshData("Models/Inverted Cube.obj"));
	}
}

void Rendering::Render()
{
	vector<MeshComponent*> meshes = App::scene->FindComponents<MeshComponent>();

	for (size_t m = 0; m < meshes.size(); m++)
	{
		MeshComponent* currentMesh = meshes[m];
		currentMesh->PreRender();

		currentMesh->shader->SetMat4("uModelMat", currentMesh->owner->transform->matrix.Get());
		currentMesh->shader->SetMat4("uProjectionMat", Rendering::outputCam->projectionMat);
		currentMesh->shader->SetMat4("uViewMat", Rendering::outputCam->viewMat.Get());

		glUseProgram(currentMesh->shader->id);
		glBindVertexArray(currentMesh->mesh->vertexArray->id);
		glBindBuffer(currentMesh->mesh->vertexArray->indexBuffer->bufferType, currentMesh->mesh->vertexArray->indexBuffer->id);

		for (size_t i = 0; i < currentMesh->shader->textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(currentMesh->shader->textures[i]->textureType, currentMesh->shader->textures[i]->id);
		}

		glDrawElements(GL_TRIANGLES, currentMesh->mesh->meshData.indices.size(), GL_UNSIGNED_INT, nullptr);
		currentMesh->PostRender();
	}

	skyboxShader->SetMat4("uProjectionMat", outputCam->projectionMat);
	skyboxShader->SetMat4("uViewMat", mat4(mat3(outputCam->viewMat.Get())));

	glUseProgram(skyboxShader->id);
	glBindVertexArray(skyboxMesh->vertexArray->id);
	glBindBuffer(skyboxMesh->vertexArray->indexBuffer->bufferType, skyboxMesh->vertexArray->indexBuffer->id);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(skybox->textureType, skybox->id);
	glDrawElements(GL_TRIANGLES, skyboxMesh->meshData.indices.size(), GL_UNSIGNED_INT, nullptr);
}

void Rendering::DebugMessage(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
	const GLchar* message, const void* userParam)
{
	cout << message << endl;
	debugMessage->Invoke(OpenGLDebugMessageInfo(source, type, id, severity, length, message, userParam));
}