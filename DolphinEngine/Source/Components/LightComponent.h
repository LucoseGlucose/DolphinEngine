#pragma once

#include "Component.h"
#include "glm/glm.hpp"
#include "LightType.h"
#include "ReadOnlyProperty.h"

using namespace glm;

class LightComponent : public Component
{


public:

	LightType type  = LightType::Point;
	vec3 color = vec3(1.f);
	float strength = 1.f;
	vec2 falloff = vec2(.09f, .032f);

	ReadOnlyProperty<vec3> output = ReadOnlyProperty<vec3>([this]() { return color * strength; });
};