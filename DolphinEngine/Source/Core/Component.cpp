#include "Component.h"

void Component::Create(SceneObject* owner)
{
	this->owner = owner;
}