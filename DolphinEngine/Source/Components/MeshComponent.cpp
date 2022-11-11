#include "MeshComponent.h"
#include "glm/gtc/type_ptr.hpp"
#include "Rendering.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

MeshComponent::~MeshComponent()
{
	delete mesh;
}