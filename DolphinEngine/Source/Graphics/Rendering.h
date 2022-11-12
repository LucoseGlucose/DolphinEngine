#pragma once

#include "Scene.h"
#include "EventArgs.h"
#include "Event.h"
#include "CameraComponent.h"
#include "Mesh.h"
#include "ShaderProgram.h"

class Rendering
{
	static inline Mesh* quad{ nullptr };
	static inline ShaderProgram* postProcessShader{ nullptr };

public:

	Rendering() = delete;

	static inline CameraComponent* outputCam{ nullptr };
	static inline Event<OpenGLDebugMessageInfo> debugMessage{ Event<OpenGLDebugMessageInfo>() };

	static inline Texture* skybox{ nullptr };
	static inline ShaderProgram* skyboxShader{ nullptr };
	static inline Mesh* skyboxMesh{ nullptr };
	static inline vec3 ambientColor{ vec3(.2f) };

	static void Init();
	static void Render();
	static void DebugMessage(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
};