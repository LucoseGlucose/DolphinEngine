#include "CameraControllerComponent.h"
#include "Input.h"
#include "Utils.h"

void CameraControllerComponent::Update()
{
	if (glfwGetMouseButton(App::window, 1))
	{
		owner->transform->rotation += vec3(Input::mouseDelta.y, -Input::mouseDelta.x, 0.f) * (float)App::deltaTime * rotationSpeed;

		if (glfwGetKey(App::window, GLFW_KEY_W))
		{
			owner->transform->position = owner->transform->position + flySpeed * (float)App::deltaTime * owner->transform->forward.Get();
		}
		if (glfwGetKey(App::window, GLFW_KEY_S))
		{
			owner->transform->position = owner->transform->position + -flySpeed * (float)App::deltaTime * owner->transform->forward.Get();
		}
		if (glfwGetKey(App::window, GLFW_KEY_A))
		{
			owner->transform->position = owner->transform->position + flySpeed * (float)App::deltaTime * owner->transform->right.Get();
		}
		if (glfwGetKey(App::window, GLFW_KEY_D))
		{
			owner->transform->position = owner->transform->position + -flySpeed * (float)App::deltaTime * owner->transform->right.Get();
		}
		if (glfwGetKey(App::window, GLFW_KEY_E))
		{
			owner->transform->position = owner->transform->position + flySpeed * (float)App::deltaTime * owner->transform->up.Get();
		}
		if (glfwGetKey(App::window, GLFW_KEY_Q))
		{
			owner->transform->position = owner->transform->position + -flySpeed * (float)App::deltaTime * owner->transform->up.Get();
		}
	}

	if (glfwGetMouseButton(App::window, 2))
	{
		owner->transform->position = owner->transform->position + panSpeed * (float)App::deltaTime *
			((float)Input::mouseDelta.x * owner->transform->right.Get() + (float)Input::mouseDelta.y * owner->transform->up.Get());
	}

	if (Input::scrollDelta.y != 0)
	{
		owner->transform->position = owner->transform->position + scrollSpeed * (float)Input::scrollDelta.y * owner->transform->forward.Get();
	}
}