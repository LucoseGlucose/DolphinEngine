#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/matrix_decompose.hpp"
#include "Property.h"
#include "Utils.h"

using namespace glm;

class Transform
{


public:

	vec3 position;
	vec3 rotation;
	vec3 scale = vec3(1.f);

	Property<mat4> matrix = Property<mat4>([this]()
		{
			return glm::translate(mat4(1.f), position) * GetMat4(rotation) * glm::scale(mat4(1.f), scale);
		},
		[this](mat4 val)
		{
			vec3 scale;
			quat rotation;
			vec3 translation;
			vec3 skew;
			vec4 perspective;
			glm::decompose(val, scale, rotation, translation, skew, perspective);

			position = translation;
			this->rotation = GetAngles(rotation);
			this->scale = scale;
		});

	Property<vec3> forward = Property<vec3>([this]() { return glm::rotate(GetQuat(rotation), vec3(0.f, 0.f, 1.f)); },
		[this](vec3 val) { rotation = GetAngles(glm::angleAxis(0.f, val)); });

	Property<vec3> up = Property<vec3>([this]() { return glm::rotate(GetQuat(rotation), vec3(0.f, 1.f, 0.f)); },
		[this](vec3 val) { rotation = GetAngles(glm::angleAxis(0.f, glm::cross(val, right.Get()))); });

	Property<vec3> right = Property<vec3>([this]() { return glm::rotate(GetQuat(rotation), vec3(1.f, 0.f, 0.f)); },
		[this](vec3 val) { rotation = GetAngles(glm::angleAxis(0.f, glm::cross(val, up.Get()))); });
};