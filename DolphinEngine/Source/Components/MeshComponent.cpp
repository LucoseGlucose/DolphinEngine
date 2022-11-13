#include "MeshComponent.h"
#include "glm/gtc/type_ptr.hpp"
#include "Rendering.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

MeshComponent::~MeshComponent()
{
	delete mesh;
}

void MeshComponent::PreRender()
{
	shader->SetMat4Cache("uModelMat", owner->transform->matrix.Get());
	shader->SetMat4Cache("uProjectionMat", Rendering::outputCam->projectionMat);
	shader->SetMat4Cache("uViewMat", Rendering::outputCam->viewMat.Get());
	shader->SetVec3Cache("uAmbientColor", Rendering::ambientColor);
	shader->SetVec3Cache("uCameraPos", Rendering::outputCam->owner->transform->position);
}

void MeshComponent::Render()
{
	shader->Bind();
	mesh->vertexArray->Bind();

	for (size_t i = 0; i < shader->textures.size(); i++)
	{
		shader->textures[i]->Bind(i + 1);
	}

	glDrawElements(GL_TRIANGLES, mesh->vertexArray->indexBuffer->size, GL_UNSIGNED_INT, nullptr);
}

void MeshComponent::PostRender()
{
	for (size_t i = 0; i < shader->textures.size(); i++)
	{
		shader->textures[i]->Unbind(i + 1);
	}
}