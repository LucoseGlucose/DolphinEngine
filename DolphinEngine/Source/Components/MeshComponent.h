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

	virtual inline void PreRender() {  }
	virtual inline void PostRender() {  }
};
