#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <optional>
#include <algorithm>
#include <format>
#include <functional>

#include "Rendering.h"
#include "MeshComponent.h"
#include "SceneObject.h"
#include "Component.h"
#include "App.h"
#include "Texture.h"
#include "LightComponent.h"
#include "LightType.h"

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
	glEnable(GL_MULTISAMPLE);

	function<void(WindowIntXYInfo)> resizeFunc = [](WindowIntXYInfo i) { glViewport(0, 0, i.x, i.y); };
	App::windowSizeChanged.Subscribe(resizeFunc);

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
	vector<LightComponent*> lights = App::scene->FindComponents<LightComponent>();

	sort(meshes.begin(), meshes.end(), [](MeshComponent* m1, MeshComponent* m2) { return glm::distance(m1->owner->transform->position,
		outputCam->owner->transform->position) > glm::distance(m2->owner->transform->position, outputCam->owner->transform->position); });

	for (size_t m = 0; m < meshes.size(); m++)
	{
		MeshComponent* currentMesh = meshes[m];
		currentMesh->PreRender();

		currentMesh->shader->SetMat4Cache("uModelMat", currentMesh->owner->transform->matrix.Get());
		currentMesh->shader->SetMat4Cache("uProjectionMat", Rendering::outputCam->projectionMat);
		currentMesh->shader->SetMat4Cache("uViewMat", Rendering::outputCam->viewMat.Get());
		currentMesh->shader->SetVec3Cache("uAmbientColor", Rendering::ambientColor);
		currentMesh->shader->SetVec3Cache("uCameraPos", Rendering::outputCam->owner->transform->position);

		sort(lights.begin(), lights.end(), [&](LightComponent* l1, LightComponent* l2) { return glm::distance(l1->owner->transform->position,
			currentMesh->owner->transform->position) > glm::distance(l2->owner->transform->position, currentMesh->owner->transform->position); });

		for (size_t i = 0; i < 5; i++)
		{
			if (i < lights.size())
			{
				if (lights[i]->type == LightType::Directional) 
					currentMesh->shader->SetVec3Cache(std::format("uLights[{}].uPosition", i), -lights[i]->owner->transform->forward.Get());
				else currentMesh->shader->SetVec3Cache(std::format("uLights[{}].uPosition", i), lights[i]->owner->transform->position);

				if (lights[i]->type == LightType::Directional) currentMesh->shader->SetVec2Cache(std::format("uLights[{}].uFalloff", i), vec2(0));
				else currentMesh->shader->SetVec2Cache(std::format("uLights[{}].uFalloff", i), lights[i]->falloff);

				currentMesh->shader->SetIntCache(std::format("uLights[{}].uType", i), lights[i]->type);
				currentMesh->shader->SetVec3Cache(std::format("uLights[{}].uColor", i), lights[i]->output.Get());
			}
			else
			{
				currentMesh->shader->SetIntCache(std::format("uLights[{}].uType", i), 0);
				currentMesh->shader->SetVec3Cache(std::format("uLights[{}].uColor", i), vec3(0));
				currentMesh->shader->SetVec3Cache(std::format("uLights[{}].uPosition", i), vec3(0));
				currentMesh->shader->SetVec2Cache(std::format("uLights[{}].uFalloff", i), vec2(0));
			}
		}

		glUseProgram(currentMesh->shader->id);
		glBindVertexArray(currentMesh->mesh->vertexArray->id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, currentMesh->mesh->vertexArray->indexBuffer->id);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(skybox->textureType, skybox->id);

		for (size_t i = 0; i < currentMesh->shader->textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE1 + i);
			glBindTexture(currentMesh->shader->textures[i]->textureType, currentMesh->shader->textures[i]->id);
		}

		glDrawElements(GL_TRIANGLES, currentMesh->mesh->meshData.indices.size(), GL_UNSIGNED_INT, nullptr);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(skybox->textureType, 0);

		for (size_t i = 0; i < currentMesh->shader->textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE1 + i);
			glBindTexture(currentMesh->shader->textures[i]->textureType, 0);
		}

		currentMesh->PostRender();
	}

	skyboxShader->SetMat4Cache("uProjectionMat", outputCam->projectionMat);
	skyboxShader->SetMat4Cache("uViewMat", outputCam->viewMat.Get());

	glUseProgram(skyboxShader->id);

	glBindVertexArray(skyboxMesh->vertexArray->id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyboxMesh->vertexArray->indexBuffer->id);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(skybox->textureType, skybox->id);

	glDrawElements(GL_TRIANGLES, skyboxMesh->meshData.indices.size(), GL_UNSIGNED_INT, nullptr);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(skybox->textureType, 0);
}

void Rendering::DebugMessage(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
	const GLchar* message, const void* userParam)
{
	cout << message << endl;
	debugMessage.Invoke(OpenGLDebugMessageInfo(source, type, id, severity, length, message, userParam));
}