#include "Input.h"

void Input::Init()
{
	App::mouseScroll->Subscribe([](WindowDoubleXYInfo i) { scrollDelta = dvec2(i.x, i.y); });
}

void Input::Update()
{
	double mouseX;
	double mouseY;
	glfwGetCursorPos(App::window, &mouseX, &mouseY);

	mousePosition = dvec2(mouseX, mouseY);
	mouseDelta = mousePosition - lastMousePos;
	lastMousePos = mousePosition;

	if (lastScroll == scrollDelta) scrollDelta = dvec2(0);
	else lastScroll = scrollDelta;
}