#include <iostream>

#include "App.h"
#include "Rendering.h"
#include "MeshComponent.h"
#include "CameraComponent.h"
#include "CameraControllerComponent.h"
#include "Input.h"

using namespace std;

void App::Run()
{
    glfwInit();

    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

    window = glfwCreateWindow(1280, 720, "DolphinEngine", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glewInit();

    SetWindowEvents();

    scene = Scene::CreateScene([](Scene* scene)
    {
        MeshComponent* mesh = scene->CreateObject("Mesh")->AddComponent<MeshComponent>();

        mesh->mesh = new Mesh(MeshData("Models/Cube.obj"));

        mesh->shader = new ShaderProgram(vector<string>{ "DefaultVert.glsl", "DefaultFrag.glsl" }, vector<int>{ GL_VERTEX_SHADER, GL_FRAGMENT_SHADER });
        mesh->shader->textures.push_back(new Texture(vector<Image*>{ new Image("Images/UV Checker.png") }, GL_TEXTURE_2D));

        CameraComponent* cam = scene->CreateObject("Camera")->AddComponent<CameraComponent>();
        cam->owner->AddComponent<CameraControllerComponent>();
        cam->owner->transform->position = vec3(0.f, 0, -5.f);
        Rendering::outputCam = cam;
    },
    "Main Level");

    Input::Init();
    scene->Init();
    Rendering::Init();

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        Input::Update();
        scene->Update();
        Rendering::Render();

        deltaTime = glfwGetTime() - totalTime;
        totalTime = glfwGetTime();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    delete scene;
}

void App::GLFWErrorMessage(int errorCode, const char* message)
{
    cout << message << endl;
    glfwError.Invoke(GLFWErrorInfo(errorCode, message));
}

void App::SetWindowEvents()
{
    glfwSetErrorCallback(GLFWErrorMessage);
    glfwSetWindowPosCallback(window, [](GLFWwindow* w, int x, int y) { windowPosChanged.Invoke(WindowIntXYInfo(w, x, y)); });
    glfwSetWindowSizeCallback(window, [](GLFWwindow* w, int x, int y) { windowSizeChanged.Invoke(WindowIntXYInfo(w, x, y)); });
    glfwSetWindowCloseCallback(window, [](GLFWwindow* w) { windowClose.Invoke(w); });
    glfwSetWindowRefreshCallback(window, [](GLFWwindow* w) { windowRefresh.Invoke(w); });
    glfwSetWindowFocusCallback(window, [](GLFWwindow* w, int focused) { windowFocusChanged.Invoke(WindowBoolInfo(w, focused)); });
    glfwSetWindowIconifyCallback(window, [](GLFWwindow* w, int minimized) { windowMinimized.Invoke(WindowBoolInfo(w, minimized)); });
    glfwSetWindowMaximizeCallback(window, [](GLFWwindow* w, int maximized) { windowMaximized.Invoke(WindowBoolInfo(w, maximized)); });
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* w, int x, int y) { windowFramebufferSizeChanged.Invoke(WindowIntXYInfo(w, x, y)); });
    glfwSetWindowContentScaleCallback(window, [](GLFWwindow* w, float x, float y) { windowContentScaleChanged.Invoke(WindowFloatXYInfo(w, x, y)); });
    glfwSetKeyCallback(window, [](GLFWwindow* w, int k, int s, int a, int m) { keyPressed.Invoke(KeyPressedInfo(w, k, s, a, m)); });
    glfwSetCharCallback(window, [](GLFWwindow* w, unsigned int c) { charPressed.Invoke(CharPressedInfo(w, c)); });
    glfwSetCharModsCallback(window, [](GLFWwindow* w, unsigned int c, int m) { charPressedWithMods.Invoke(CharModsInfo(w, c, m)); });
    glfwSetMouseButtonCallback(window, [](GLFWwindow* w, int b, int a, int m) { mousePressed.Invoke(MouseButtonInfo(w, b, a, m)); });
    glfwSetCursorPosCallback(window, [](GLFWwindow* w, double x, double y) { mouseMoved.Invoke(WindowDoubleXYInfo(w, x, y)); });
    glfwSetCursorEnterCallback(window, [](GLFWwindow* w, int e) { mouseEnterWindow.Invoke(WindowBoolInfo(w, e)); });
    glfwSetScrollCallback(window, [](GLFWwindow* w, double x, double y) { mouseScroll.Invoke(WindowDoubleXYInfo(w, x, y)); });
    glfwSetDropCallback(window, [](GLFWwindow* w, int c, const char** f) { fileDrop.Invoke(FileDropInfo(w, c, f)); });
    glfwSetJoystickCallback([](int i, int e) { joystickEvent.Invoke(JoystickInfo(i, e)); });
}