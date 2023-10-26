#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

class FlyingCamera {
public:
    FlyingCamera(GLFWwindow* window, glm::vec3 initialPosition, float initialSpeed, float sensitivity);

    void Update(float deltaTime);
    glm::mat4 GetViewMatrix() const;
    
    // Setters for camera parameters
    void SetPosition(glm::vec3 position);
    void SetSpeed(float speed);
    void SetSensitivity(float sensitivity);

    // Handle keyboard input
    void ProcessKeyboardInput(int key, bool isPressed);
    
    // Handle mouse input
    void ProcessMouseMovement(float xOffset, float yOffset);

private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;

    GLFWwindow* window;

    float yaw;
    float pitch;

    float movementSpeed;
    float mouseSensitivity;
    float zoom;

    bool firstMouse;
    float lastX;
    float lastY;

    void UpdateCameraVectors();
};
