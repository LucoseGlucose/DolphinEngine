#pragma once

#include "Component.h"
#include "CameraComponent.h"
#include "Mesh.h"
#include "ShaderProgram.h"

class MeshComponent : public Component
{


public:

	~MeshComponent();

	Mesh* mesh;
	ShaderProgram* shader;

	virtual void PreRender();
	virtual void Render();
	virtual void PostRender();
};
