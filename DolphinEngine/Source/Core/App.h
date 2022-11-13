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
		},
		[](ivec2 val)
		{
			glfwSetWindowSize(window, val.x, val.y);
		})};

	static inline double totalTime{ 0 };
	static inline double deltaTime{ 0 };

	static inline Event<GLFWErrorInfo> glfwError;
	static inline Event<WindowMonitorInfo> moniterEvent{ Event<WindowMonitorInfo>() };
	static inline Event<WindowIntXYInfo> windowPosChanged{ Event<WindowIntXYInfo>() };
	static inline Event<WindowIntXYInfo> windowSizeChanged{ Event<WindowIntXYInfo>() };
	static inline Event<GLFWwindow*> windowClose{ Event<GLFWwindow*>() };
	static inline Event<GLFWwindow*> windowRefresh{ Event<GLFWwindow*>() };
	static inline Event<WindowBoolInfo> windowFocusChanged{ Event<WindowBoolInfo>() };
	static inline Event<WindowBoolInfo> windowMinimized{ Event<WindowBoolInfo>() };
	static inline Event<WindowBoolInfo> windowMaximized{ Event<WindowBoolInfo>() };
	static inline Event<WindowIntXYInfo> windowFramebufferSizeChanged{ Event<WindowIntXYInfo>() };
	static inline Event<WindowFloatXYInfo> windowContentScaleChanged{ Event<WindowFloatXYInfo>() };
	static inline Event<KeyPressedInfo> keyPressed{ Event<KeyPressedInfo>() };
	static inline Event<CharPressedInfo> charPressed{ Event<CharPressedInfo>() };
	static inline Event<CharModsInfo> charPressedWithMods{ Event<CharModsInfo>() };
	static inline Event<MouseButtonInfo> mousePressed{ Event<MouseButtonInfo>() };
	static inline Event<WindowDoubleXYInfo> mouseMoved{ Event<WindowDoubleXYInfo>() };
	static inline Event<WindowBoolInfo> mouseEnterWindow{ Event<WindowBoolInfo>() };
	static inline Event<WindowDoubleXYInfo> mouseScroll{ Event<WindowDoubleXYInfo>() };
	static inline Event<FileDropInfo> fileDrop{ Event<FileDropInfo>() };
	static inline Event<JoystickInfo> joystickEvent{ Event<JoystickInfo>() };

	static void Run();
	static void GLFWErrorMessage(int errorCode, const char* message);
};