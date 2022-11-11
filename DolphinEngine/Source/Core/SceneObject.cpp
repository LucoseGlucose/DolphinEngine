#include "SceneObject.h"

SceneObject::SceneObject(const string& name)
{
	this->name = name;
}

SceneObject::~SceneObject()
{
	for (size_t i = 0; i < components.size(); i++)
	{
		RemoveComponent(components[i]);
	}
}

void SceneObject::Update()
{
	for (size_t i = 0; i < components.size(); ++i)
	{
		components[i]->Update();
	}
}

void SceneObject::RemoveComponent(Component* component)
{
	components.erase(ranges::remove(components, component).begin());
	delete component;
}