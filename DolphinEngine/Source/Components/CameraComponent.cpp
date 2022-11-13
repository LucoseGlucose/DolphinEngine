#include "CameraComponent.h"

CameraComponent::~CameraComponent()
{
	App::windowSizeChanged.Unsubscribe(resizeFuncIndex);
	delete output;
}

void CameraComponent::Create(SceneObject* owner)
{
	Component::Create(owner);

	function<void(WindowIntXYInfo)> resizeFunc = [this](WindowIntXYInfo i)
	{
		if (!matchScreen) return;
		size = vec2(i.x, i.y);
		CreateNewFrameBuffer(i.x, i.y);
	};
	resizeFuncIndex = App::windowSizeChanged.Subscribe(resizeFunc);

	CreateNewFrameBuffer(App::windowSize.Get().x, App::windowSize.Get().y);
}

void CameraComponent::CreateNewFrameBuffer(int xSize, int ySize)
{
	if (output != nullptr) delete output;

	Texture* colorTex = new Texture(xSize, ySize, nullptr, GL_TEXTURE_2D);
	Texture* normalTex = new Texture(xSize, ySize, nullptr, GL_TEXTURE_2D);
	Texture* materialTex = new Texture(xSize, ySize, nullptr, GL_TEXTURE_2D);
	Texture* depthTex = new Texture(xSize, ySize, nullptr, GL_TEXTURE_2D, GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT);

	output = new FrameBuffer(vector<Texture*>{ colorTex, normalTex, materialTex, depthTex }, vector<RenderBuffer*>{  },
		vector<int>{ GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_DEPTH_ATTACHMENT });
}