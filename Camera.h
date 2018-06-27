#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

enum class CameraMovement {
    Forward,
    Backward,
    Left, 
    Right
};

class Camera {
public:
    Camera(const glm::vec3& position, const glm::vec3& up, float yaw, float pitch);
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

    glm::mat4 getViewMatrix() const;

    void processKeyboard(const CameraMovement& direction, float deltaTime);
    void processMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch);
    void processMouseScrolls(float yOffset);

    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;
    float zoom = 45.0f;

private:
    void updateCameraVectors();

    float m_yaw = -90.0f;
    float m_pitch = 0.0f;
    
    float m_movementSpeed = 2.5f;
    float m_mouseSensitivity = 0.1f;
};