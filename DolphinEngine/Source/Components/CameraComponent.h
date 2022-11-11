#pragma once

#include <vector>

#include "Component.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ReadOnlyProperty.h"
#include "SceneObject.h"
#include "App.h"

using namespace glm;
using namespace std;

class CameraComponent : public Component
{


public:

	mat4 projectionMat = glm::perspective(glm::radians(60.f), (float)App::windowSize.Get().x / App::windowSize.Get().y, .1f, 100.f);

	ReadOnlyProperty<mat4> viewMat = ReadOnlyProperty<mat4>([this]()
		{
			return glm::lookAt(owner->transform->position,
				owner->transform->position + owner->transform->forward.Get(), owner->transform->up.Get());
		});
};