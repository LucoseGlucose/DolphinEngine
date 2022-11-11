#pragma once

#include <vector>
#include <optional>
#include <memory>
#include <string>
#include <functional>

#include "SceneObject.h"

using namespace std;

class Scene
{
	vector<SceneObject*> sceneObjects;

public:

	Scene(const string& name);
	~Scene();

	string name;

	static Scene* CreateScene(const function<void(Scene*)>& func, const string& sceneName);
	void Init();
	void Update() const;
	SceneObject* CreateObject(const string& objName);
	void DestroyObject(SceneObject* obj);

	template<typename T> optional<T*> FindComponent();
	template<typename T> vector<T*> FindComponents();
};

template<typename T>
optional<T*> Scene::FindComponent()
{
	for (size_t i = 0; i < sceneObjects.size(); i++)
	{
		optional<T*> comp = sceneObjects[i]->GetComponent<T>();
		if (comp.has_value()) return comp;
	}

	return nullopt;
}

template<typename T>
vector<T*> Scene::FindComponents()
{
	vector<T*> vec;

	for (size_t i = 0; i < sceneObjects.size(); i++)
	{
		vector<T*> comps = sceneObjects[i]->GetComponents<T>();

		for (size_t c = 0; c < comps.size(); c++)
		{
			vec.push_back(comps[c]);
		}
	}
	
	return vec;
}
