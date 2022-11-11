#pragma once

#include <vector>
#include <optional>
#include <memory>
#include <string>
#include <algorithm>

#include "Component.h"
#include "Transform.h"

using namespace std;

class SceneObject
{
	vector<Component*> components;

public:

	SceneObject(const string& name);
	~SceneObject();

	string name;
	Transform* transform = new Transform();

	void Update();

	template<typename T> optional<T*> GetComponent();
	template<typename T> vector<T*> GetComponents();
	template<typename T> T* AddComponent();
	void RemoveComponent(Component* component);
};

template<typename T>
optional<T*> SceneObject::GetComponent()
{
	for (size_t i = 0; i < components.size(); i++)
	{
		T* comp = dynamic_cast<T*>(components[i]);
		if (comp != nullptr) return optional<T*>{ comp };
	}

	return nullopt;
}

template<typename T>
vector<T*> SceneObject::GetComponents()
{
	vector<T*> vec;

	for (size_t i = 0; i < components.size(); i++)
	{
		optional<T*> comp = GetComponent<T>();
		if (comp.has_value()) vec.push_back(comp.value());
	}
	
	return vec;
}

template <typename T>
T* SceneObject::AddComponent()
{
	T* t = new T();

	Component* comp = dynamic_cast<Component*>(t);
	if (comp == nullptr) return nullptr;

	comp->Create(this);
	components.push_back(comp);

	return t;
}