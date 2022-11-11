#include "Scene.h"

#include <functional>
#include <algorithm>

Scene::Scene(const string& name)
{
	this->name = name;
}

Scene::~Scene()
{
	for (size_t i = 0; i < sceneObjects.size(); i++)
	{
		DestroyObject(sceneObjects[i]);
	}
}

void Scene::Init()
{

}

void Scene::Update() const
{
	for (size_t i = 0; i < sceneObjects.size(); ++i)
	{
		sceneObjects[i]->Update();
	}
}

SceneObject* Scene::CreateObject(const string& objName)
{
	SceneObject* obj = new SceneObject(objName);
	sceneObjects.push_back(obj);
	return obj;
}

void Scene::DestroyObject(SceneObject* obj)
{
	sceneObjects.erase(ranges::remove(sceneObjects, obj).begin());
	delete obj;
}

Scene* Scene::CreateScene(const function<void(Scene*)>& func, const string& sceneName)
{
	Scene* scene = new Scene(sceneName);
	func(scene);
	return scene;
}