#pragma once

#include <vector>
#include <functional>

#include "Component.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ReadOnlyProperty.h"
#include "SceneObject.h"
#include "App.h"
#include "EventArgs.h"
#include "FrameBuffer.h"

using namespace glm;
using namespace std;

class CameraComponent : public Component
{
	int resizeFuncIndex;

public:

	~CameraComponent();

	virtual void Create(SceneObject* owner) override;

	FrameBuffer* output;
	float fov = 60.f;
	vec2 size = vec2(App::windowSize.Get().x, App::windowSize.Get().y);
	float nearClip = .1f;
	float farClip = 100.f;
	bool orthographic = false;
	bool matchScreen = true;
	vec2 orthoSize = vec2(16, 9);

	ReadOnlyProperty<mat4> projectionMat = ReadOnlyProperty<mat4>([this]()
		{
			if (!orthographic) return glm::perspective(glm::radians(fov), size.x / size.y, nearClip, farClip);
			else return glm::ortho(orthoSize.x * -.5f, orthoSize.x * .5f, orthoSize.y * -.5f, orthoSize.y * .5f, nearClip, farClip);
		});

	ReadOnlyProperty<mat4> viewMat = ReadOnlyProperty<mat4>([this]()
		{
			return glm::lookAt(owner->transform->position,
				owner->transform->position + owner->transform->forward.Get(), owner->transform->up.Get());
		});
};