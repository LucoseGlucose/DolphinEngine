#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct OpenGLDebugMessageInfo
{
	OpenGLDebugMessageInfo(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

	GLenum source;
	GLenum type;
	GLuint id;
	GLenum severity;
	GLsizei length;
	const GLchar* message;
	const void* userParam;
};

struct WindowMonitorInfo
{
	WindowMonitorInfo(GLFWmonitor* moniter, int event);

	GLFWmonitor* moniter;
	int event;
};

struct GLFWErrorInfo
{
	GLFWErrorInfo(int errorCode, const char* message);

	int errorCode;
	const char* message;
};

struct WindowIntXYInfo
{
	WindowIntXYInfo(GLFWwindow* window, int x, int y);

	GLFWwindow* window;
	int x;
	int y;
};

struct WindowBoolInfo
{
	WindowBoolInfo(GLFWwindow* window, bool enabled);

	GLFWwindow* window;
	bool enabled;
};

struct WindowFloatXYInfo
{
	WindowFloatXYInfo(GLFWwindow* window, float x, float y);

	GLFWwindow* window;
	float x;
	float y;
};

struct WindowDoubleXYInfo
{
	WindowDoubleXYInfo(GLFWwindow* window, double x, double y);

	GLFWwindow* window;
	double x;
	double y;
};

struct KeyPressedInfo
{
	KeyPressedInfo(GLFWwindow* window, int key, int scancode, int action, int mods);

	GLFWwindow* window;
	int key;
	int scancode;
	int action;
	int mods;
};

struct CharPressedInfo
{
	CharPressedInfo(GLFWwindow* window, unsigned int charCode);

	GLFWwindow* window;
	int charCode;
};

struct CharModsInfo
{
	CharModsInfo(GLFWwindow* window, unsigned int charCode, int mods);

	GLFWwindow* window;
	unsigned int charCode;
	int mods;
};

struct MouseButtonInfo
{
	MouseButtonInfo(GLFWwindow* window, int button, int action, int mods);

	GLFWwindow* window;
	int button;
	int action;
	int mods;
};

struct FileDropInfo
{
	FileDropInfo(GLFWwindow* window, int fileCount, const char** paths);

	GLFWwindow* window;
	int fileCount;
	const char** paths;
};

struct JoystickInfo
{
	JoystickInfo(int id, int event);

	int id;
	int event;
};