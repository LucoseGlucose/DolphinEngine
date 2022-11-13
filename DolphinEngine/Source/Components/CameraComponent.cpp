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

		delete output;

		Texture* tex = new Texture(App::windowSize.Get().x, App::windowSize.Get().y, nullptr, GL_TEXTURE_2D);
		RenderBuffer* rb = new RenderBuffer(GL_DEPTH24_STENCIL8, App::windowSize.Get().x, App::windowSize.Get().y);

		output = new FrameBuffer(vector<Texture*>{ tex }, vector<RenderBuffer*>{ rb }, vector<int>{ GL_COLOR_ATTACHMENT0, GL_DEPTH_STENCIL_ATTACHMENT });
	};
	resizeFuncIndex = App::windowSizeChanged.Subscribe(resizeFunc);

	Texture* tex = new Texture(App::windowSize.Get().x, App::windowSize.Get().y, nullptr, GL_TEXTURE_2D);
	RenderBuffer* rb = new RenderBuffer(GL_DEPTH24_STENCIL8, App::windowSize.Get().x, App::windowSize.Get().y);

	output = new FrameBuffer(vector<Texture*>{ tex }, vector<RenderBuffer*>{ rb }, vector<int>{ GL_COLOR_ATTACHMENT0, GL_DEPTH_STENCIL_ATTACHMENT });
}