#include "camera.h"

FlyingCamera::FlyingCamera(GLFWwindow* window, glm::vec3 initialPosition, float initialSpeed, float sensitivity)
    : position(initialPosition), front(glm::vec3(0.0f, 0.0f, -1.0f)), up(glm::vec3(0.0f, 1.0f, 0.0f)),
      right(glm::cross(front, up)), yaw(-90.0f), pitch(0.0f),
      movementSpeed(initialSpeed), mouseSensitivity(sensitivity), zoom(45.0f),
      firstMouse(true), lastX(0.0f), lastY(0.0f), window(window) {
}


void FlyingCamera::Update(float deltaTime) {
    // Update the camera's state based on user input (WASD movement)
    // Implement the camera's movement logic here
}

glm::mat4 FlyingCamera::GetViewMatrix() const {
    // Calculate and return the view matrix
    return glm::lookAt(position, position + front, up);
}

void FlyingCamera::SetPosition(glm::vec3 newPosition) {
    position = newPosition;
}

void FlyingCamera::SetSpeed(float newSpeed) {
    movementSpeed = newSpeed;
}

void FlyingCamera::SetSensitivity(float newSensitivity) {
    mouseSensitivity = newSensitivity;
}

void FlyingCamera::ProcessKeyboardInput(int key, bool isPressed) {
   
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        position += movementSpeed * front;
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        position -= movementSpeed * front;
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        position -= glm::normalize(glm::cross(front, up)) * movementSpeed;
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        position += glm::normalize(glm::cross(front, up)) * movementSpeed;

}

void FlyingCamera::ProcessMouseMovement(float xOffset, float yOffset) {
    // Process mouse movement to update camera orientation (yaw and pitch)
    // Implement mouse movement logic based on input
}

void FlyingCamera::UpdateCameraVectors() {
    // Update the camera's orientation vectors (front, right, up) based on yaw and pitch
    // Implement the update logic
}
