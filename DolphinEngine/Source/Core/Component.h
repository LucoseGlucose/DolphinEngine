#pragma once

#include "ReadOnlyProperty.h"
#include "Transform.h"

class SceneObject;

class Component
{

public:

	Component() = default;

	SceneObject* owner;

	virtual void Create(SceneObject* owner);
	virtual inline void Update() {  }
};