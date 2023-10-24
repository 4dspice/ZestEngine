#include "window.h"

Window::Window(int width, int height, const char* title) {
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

Window::~Window() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

GLFWwindow* Window::GetWindow() const {
    return window;
}

void Window::MakeContextCurrent() const {
    glfwMakeContextCurrent(window);
}

void Window::SwapBuffers() const {
    glfwSwapBuffers(window);
}

bool Window::ShouldClose() const {
    return glfwWindowShouldClose(window);
}

void Window::WindowCloseCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void Window::SetCallback() {
    glfwSetKeyCallback(window, WindowCloseCallback);
}

void Window::FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}