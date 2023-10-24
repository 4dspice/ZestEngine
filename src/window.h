#pragma once

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
public:
    Window(int width, int height, const char* title);
    ~Window();
    GLFWwindow* GetWindow() const;
    void MakeContextCurrent() const;
    void SwapBuffers() const;
    bool ShouldClose() const;

    void SetCallback();

private:
    GLFWwindow* window;
    static void WindowCloseCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
};
