#include "window.h"

GLFWWindow::GLFWWindow(int width, int height, const char* title) {
    if (!glfwInit()) {
        // Handle initialization error
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window) {
        std::cerr << "Error! Could not create GLFW window" << std::endl;
        glfwTerminate();
        // Handle window creation error
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cerr << "Error! Could not load glad" << std::endl;
        glfwTerminate();
        // Handle GLAD initialization error
    }
}

GLFWWindow::~GLFWWindow() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

GLFWwindow* GLFWWindow::GetWindow() const {
    return window;
}

void GLFWWindow::MakeContextCurrent() const {
    glfwMakeContextCurrent(window);
}

void GLFWWindow::SwapBuffers() const {
    glfwSwapBuffers(window);
}

bool GLFWWindow::ShouldClose() const {
    return glfwWindowShouldClose(window);
}

void GLFWWindow::WindowCloseCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void GLFWWindow::SetCallback() {
    glfwSetKeyCallback(window, WindowCloseCallback);
}