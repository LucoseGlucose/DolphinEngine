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
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LEQUAL);

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

		skybox->Bind(0);
	}

	if (skyboxShader == nullptr)
	{
		skyboxShader = new ShaderProgram(vector<string>{ "SkyboxVert.glsl", "SkyboxFrag.glsl" }, vector<int>{ GL_VERTEX_SHADER, GL_FRAGMENT_SHADER });
	}

	if (skyboxMesh == nullptr)
	{
		skyboxMesh = new Mesh(MeshData("Models/Inverted Cube.obj"));
	}

	if (quad == nullptr)
	{
		quad = new Mesh(MeshData("Models/Quad.obj"));
	}

	if (postProcessShader == nullptr)
	{
		postProcessShader = new ShaderProgram(vector<string>{ "PostProcessVert.glsl", "PostProcessFrag.glsl" },
			vector<int>{ GL_VERTEX_SHADER, GL_FRAGMENT_SHADER });
	}
}

void Rendering::Render()
{
	outputCam->output->Bind();
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	vector<MeshComponent*> meshes = App::scene->FindComponents<MeshComponent>();
	vector<LightComponent*> lights = App::scene->FindComponents<LightComponent>();

	sort(meshes.begin(), meshes.end(), [](MeshComponent* m1, MeshComponent* m2) { return glm::distance(m1->owner->transform->position,
		outputCam->owner->transform->position) > glm::distance(m2->owner->transform->position, outputCam->owner->transform->position); });

	for (size_t m = 0; m < meshes.size(); m++)
	{
		MeshComponent* currentMesh = meshes[m];
		currentMesh->PreRender();

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

		currentMesh->Render();
		currentMesh->PostRender();
	}

	skyboxShader->SetMat4Cache("uProjectionMat", outputCam->projectionMat);
	skyboxShader->SetMat4Cache("uViewMat", outputCam->viewMat.Get());

	RenderMesh(skyboxMesh, skyboxShader);

	outputCam->output->Unbind();
	glDisable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (size_t i = 0; i < outputCam->output->textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE1 + i);
		glBindTexture(outputCam->output->textures[i]->textureType, outputCam->output->textures[i]->id);
	}

	RenderMesh(quad, postProcessShader);
}

void Rendering::RenderMesh(Mesh* mesh, ShaderProgram* shader)
{
	shader->Bind();
	mesh->vertexArray->Bind();

	for (size_t i = 0; i < shader->textures.size(); i++)
	{
		shader->textures[i]->Bind(i + 1);
	}

	glDrawElements(GL_TRIANGLES, mesh->vertexArray->indexBuffer->size, GL_UNSIGNED_INT, nullptr);

	for (size_t i = 0; i < shader->textures.size(); i++)
	{
		shader->textures[i]->Unbind(i + 1);
	}
}

void Rendering::DebugMessage(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
	const GLchar* message, const void* userParam)
{
	cout << message << endl;
	debugMessage.Invoke(OpenGLDebugMessageInfo(source, type, id, severity, length, message, userParam));
}