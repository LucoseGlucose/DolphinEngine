#include "CameraComponent.h"

CameraComponent::~CameraComponent()
{
	App::windowSizeChanged.Unsubscribe(resizeFuncIndex);
}

void CameraComponent::Create(SceneObject* owner)
{
	Component::Create(owner);

	function<void(WindowIntXYInfo)> resizeFunc = [this](WindowIntXYInfo i) { if (matchScreen) size = vec2(i.x, i.y); };
	resizeFuncIndex = App::windowSizeChanged.Subscribe(resizeFunc);
}