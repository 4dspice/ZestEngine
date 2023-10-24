#pragma once

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class GLFWWindow {
public:
    GLFWWindow(int width, int height, const char* title);
    ~GLFWWindow();
    GLFWwindow* GetWindow() const;
    void MakeContextCurrent() const;
    void SwapBuffers() const;
    bool ShouldClose() const;

    void SetCallback();
    
private:
    GLFWwindow* window;
    static void WindowCloseCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

};
