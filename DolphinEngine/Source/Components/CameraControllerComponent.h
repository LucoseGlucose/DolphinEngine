#pragma once

#include "Component.h"
#include "App.h"

class CameraControllerComponent : public Component
{
	vec2 lastCursorPos;

public:

	virtual void Update() override;

	float rotationSpeed = 300.f;
	float panSpeed = 25.f;
	float flySpeed = 10.f;
	float scrollSpeed = 1.f;
};