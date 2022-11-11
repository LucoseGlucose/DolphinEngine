#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>

#include "Scene.h"
#include "EventArgs.h"
#include "Event.h"

class App
{
	static void SetWindowEvents();

public:

	App() = delete;

	static inline GLFWwindow* window{ nullptr };
	static inline Scene* scene{ nullptr };

	static inline Property<ivec2> windowSize{ Property<ivec2>([]()
		{
			int width;
			int height;
			glfwGetWindowSize(window, &width, &height);
			
			return ivec2(width, height);
		}, [](ivec2 val)
		{
			glfwSetWindowSize(window, val.x, val.y);
		})};

	static inline double totalTime{ 0 };
	static inline double deltaTime{ 0 };

	static inline Event<GLFWErrorInfo>* glfwError;
	static inline Event<WindowMonitorInfo>* moniterEvent{ new Event<WindowMonitorInfo>() };
	static inline Event<WindowIntXYInfo>* windowPosChanged{ new Event<WindowIntXYInfo>() };
	static inline Event<WindowIntXYInfo>* windowSizeChanged{ new Event<WindowIntXYInfo>() };
	static inline Event<GLFWwindow*>* windowClose{ new Event<GLFWwindow*>() };
	static inline Event<GLFWwindow*>* windowRefresh{ new Event<GLFWwindow*>() };
	static inline Event<WindowBoolInfo>* windowFocusChanged{ new Event<WindowBoolInfo>() };
	static inline Event<WindowBoolInfo>* windowMinimized{ new Event<WindowBoolInfo>() };
	static inline Event<WindowBoolInfo>* windowMaximized{ new Event<WindowBoolInfo>() };
	static inline Event<WindowIntXYInfo>* windowFramebufferSizeChanged{ new Event<WindowIntXYInfo>() };
	static inline Event<WindowFloatXYInfo>* windowContentScaleChanged{ new Event<WindowFloatXYInfo>() };
	static inline Event<KeyPressedInfo>* keyPressed{ new Event<KeyPressedInfo>() };
	static inline Event<CharPressedInfo>* charPressed{ new Event<CharPressedInfo>() };
	static inline Event<CharModsInfo>* charPressedWithMods{ new Event<CharModsInfo>() };
	static inline Event<MouseButtonInfo>* mousePressed{ new Event<MouseButtonInfo>() };
	static inline Event<WindowDoubleXYInfo>* mouseMoved{ new Event<WindowDoubleXYInfo>() };
	static inline Event<WindowBoolInfo>* mouseEnterWindow{ new Event<WindowBoolInfo>() };
	static inline Event<WindowDoubleXYInfo>* mouseScroll{ new Event<WindowDoubleXYInfo>() };
	static inline Event<FileDropInfo>* fileDrop{ new Event<FileDropInfo>() };
	static inline Event<JoystickInfo>* joystickEvent{ new Event<JoystickInfo>() };

	static void Run();
	static void GLFWErrorMessage(int errorCode, const char* message);
};