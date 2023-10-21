#include "Camera.h"
#include <GLFW/glfw3.h>
#include <iostream>

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, float startYaw, float startPitch)
    : position(startPosition), worldUp(startUp), yaw(startYaw), pitch(startPitch)
{
    front = glm::vec3(0.0f, 0.0f, -1.0f);
    updateCameraVectors();
}

glm::mat4 Camera::calculateViewMatrix()
{
    return glm::lookAt(position, position + front, up);
}

void Camera::processKeyboardInput(bool forward, bool backward, bool left, bool right, float deltaTime)
{
    float velocity = moveSpeed * deltaTime;
    if (forward)
        position += front * velocity;
    if (backward)
        position -= front * velocity;
    if (right) 
        position += glm::normalize(glm::cross(front, up)) * velocity;
    if (left) 
        position -= glm::normalize(glm::cross(front, up)) * velocity;

    // Debugging output
    std::cout << "Position: " << position.x << ", " << position.y << ", " << position.z << std::endl;
    std::cout << "Front: " << front.x << ", " << front.y << ", " << front.z << std::endl;
    std::cout << "DeltaTime: " << deltaTime << std::endl;
}

void Camera::processMouseMovement(float xOffset, float yOffset)
{
    float sensitivity = 0.1f;
    xOffset *= mouseSensitivity;
    yOffset *= mouseSensitivity;

    yaw += xOffset;
    pitch += yOffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    updateCameraVectors();
}

void Camera::updateCameraVectors()
{
    glm::vec3 newFront;
    newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    newFront.y = sin(glm::radians(pitch));
    newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(newFront);
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));

    // Also re-calculate the Right and Up vector
    this->right = glm::normalize(glm::cross(this->front, worldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    this->up    = glm::normalize(glm::cross(this->right, this->front));
}
