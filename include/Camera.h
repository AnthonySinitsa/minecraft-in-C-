#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
    glm::vec3 position;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 front;
    glm::vec3 worldUp;

    float yaw;
    float pitch;

    Camera(glm::vec3 startPosition = glm::vec3(0.0f, 0.0f, 0.0f), 
           glm::vec3 startUp = glm::vec3(0.0f, 1.0f, 0.0f), 
           float startYaw = -90.0f, 
           float startPitch = 0.0f);

    glm::mat4 calculateViewMatrix();

    void processKeyboardInput(bool forward, bool backward, bool left, bool right, float deltaTime);
    void processMouseMovement(float xOffset, float yOffset);

private:
    float moveSpeed = 2.5f;
    float mouseSensitivity = 0.1f;

    void updateCameraVectors();
};

#endif // CAMERA_H
