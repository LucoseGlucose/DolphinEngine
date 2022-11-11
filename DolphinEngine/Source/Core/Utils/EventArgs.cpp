#include "EventArgs.h"

OpenGLDebugMessageInfo::OpenGLDebugMessageInfo(GLenum source, GLenum type, GLuint id, 
	GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	this->source = source;
	this->type = type;
	this->id = id;
	this->severity = severity;
	this->length = length;
	this->message = message;
	this->userParam = userParam;
}

WindowMonitorInfo::WindowMonitorInfo(GLFWmonitor* moniter, int event)
{
	this->moniter = moniter;
	this->event = event;
}

GLFWErrorInfo::GLFWErrorInfo(int errorCode, const char* message)
{
	this->errorCode = errorCode;
	this->message = message;
}

WindowIntXYInfo::WindowIntXYInfo(GLFWwindow* window, int x, int y)
{
	this->window = window;
	this->x = x;
	this->y = y;
}

WindowBoolInfo::WindowBoolInfo(GLFWwindow* window, bool enabled)
{
	this->window = window;
	this->enabled = enabled;
}

WindowFloatXYInfo::WindowFloatXYInfo(GLFWwindow* window, float x, float y)
{
	this->window = window;
	this->x = x;
	this->y = y;
}

WindowDoubleXYInfo::WindowDoubleXYInfo(GLFWwindow* window, double x, double y)
{
	this->window = window;
	this->x = x;
	this->y = y;
}

KeyPressedInfo::KeyPressedInfo(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	this->window = window;
	this->key = key;
	this->scancode = scancode;
	this->action = action;
	this->mods = mods;
}

CharPressedInfo::CharPressedInfo(GLFWwindow* window, unsigned int charCode)
{
	this->window = window;
	this->charCode = charCode;
}

CharModsInfo::CharModsInfo(GLFWwindow* window, unsigned int charCode, int mods)
{
	this->window = window;
	this->charCode = charCode;
	this->mods = mods;
}

MouseButtonInfo::MouseButtonInfo(GLFWwindow* window, int button, int action, int mods)
{
	this->window = window;
	this->button = button;
	this->action = action;
	this->mods = mods;
}

FileDropInfo::FileDropInfo(GLFWwindow* window, int fileCount, const char** paths)
{
	this->window = window;
	this->fileCount = fileCount;
	this->paths = paths;
}

JoystickInfo::JoystickInfo(int id, int event)
{
	this->id = id;
	this->event = event;
}