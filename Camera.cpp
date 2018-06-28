#include "Camera.h"

Camera::Camera(const glm::vec3& position, const glm::vec3& up, float yaw, float pitch)
        : position(position)
        , worldUp(up)
        , m_yaw(yaw)
        , m_pitch(pitch)
{
    updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
    : position(posX, posY, posZ)
    , worldUp(upX, upY, upZ)
    , m_yaw(yaw)
    , m_pitch(pitch)
{
    updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, position + front, up);
}

void Camera::processKeyboard(const CameraMovement& direction, float deltaTime)
{
    float velocity = m_movementSpeed * deltaTime;
    switch(direction) {
        case CameraMovement::Forward :
            position += front * velocity;
            break;
        case CameraMovement::Backward :
            position -= front * velocity;
            break;
        case CameraMovement::Right :
            position += right * velocity;
            break;
        case CameraMovement::Left :
            position -= right * velocity;
            break;
    }
}

void Camera::processMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch)
{
    xOffset *= m_mouseSensitivity;
    yOffset *= m_mouseSensitivity;

    m_yaw += xOffset;
    m_pitch += yOffset;

    if(constrainPitch)
    {
        if(m_pitch >= 89.0f) {
            m_pitch = 89.0f;
        }
        if(m_pitch <= -89.0f) {
            m_pitch = -89.0f;
        }
    }

    updateCameraVectors();
}

void Camera::processMouseScrolls(float yOffset) {
    if (zoom >= 1.0f && zoom <= 45.0f)
        zoom -= yOffset;
    if (zoom <= 1.0f)
        zoom = 1.0f;
    if (zoom >= 45.0f)
        zoom = 45.0f;
}

void Camera::updateCameraVectors() {
        glm::vec3 l_front;
        l_front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
        l_front.y = sin(glm::radians(m_pitch));
        l_front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
        front = glm::normalize(l_front);
        // Also re-calculate the Right and Up vector
        right = glm::normalize(glm::cross(front, worldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        up    = glm::normalize(glm::cross(right, front));
}