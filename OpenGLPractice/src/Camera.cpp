#include "Camera.h"
#include <GLFW/glfw3.h>

Camera::Camera(CameraType type, float screenWidth, float screenHeight)
    : type(type), screenWidth(screenWidth), screenHeight(screenHeight)
{
    moveSpeed = 0.05f;
    sensitivity = 0.05f;
    pitch = 0.0f;
    yaw = -90.0f; // Looking -z direction by default

    position = std::make_unique<glm::vec3>(0.0f, 0.0f, 3.0f);
    forward = std::make_unique<glm::vec3>(0.0f, 0.0f, -1.0f);
    up = std::make_unique<glm::vec3>(0.0f, 1.0f, 0.0f);

    view = glm::mat4(1.0f);
    proj = glm::mat4(1.0f);

    SetType(type);
}

Camera::~Camera()
{
}

void Camera::UpdateView()
{
    float radius = 10.0f;
    float camX = sin(glfwGetTime()) * radius;
    float camZ = cos(glfwGetTime()) * radius;

    view = glm::lookAt(*position, *position + *forward, *up);
}

void Camera::SetType(CameraType newType)
{
    type = newType;

    if (type == PERSPECTIVE)
    {
        proj = glm::perspective(glm::radians(45.0f), screenWidth / screenHeight, 0.1f, 100.0f);
    }
    else if (type == ORTHOGRAPHIC)
    {
        proj = glm::ortho(0.0f, screenWidth, 0.0f, screenHeight, -1.0f, 100.0f);
    }
}

void Camera::MoveForward()
{
    *position += *forward * moveSpeed;
}

void Camera::MoveBackward()
{
    *position -= *forward * moveSpeed;
}

void Camera::MoveLeft()
{
    *position -= glm::normalize(glm::cross(*forward, *up)) * moveSpeed;
}

void Camera::MoveRight()
{
    *position += glm::normalize(glm::cross(*forward, *up)) * moveSpeed;
}

void Camera::Rotate(float xOffset, float yOffset)
{
    pitch += yOffset * sensitivity;
    yaw += xOffset * sensitivity;

    if (pitch > 89.0f)
        pitch = 89.0f;
    else if (pitch < -89.0f)
        pitch = -89.0f;

    forward->x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    forward->y = sin(glm::radians(pitch));
    forward->z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    *forward = glm::normalize(*forward);
}
