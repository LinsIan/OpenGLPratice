#include "Camera.h"
Camera::Camera(CameraType type, float screenWidth, float screenHeight)
    : type(type), screenWidth(screenWidth), screenHeight(screenHeight),
      translation(std::make_unique<glm::vec3>(0.0f, 0.0f, -3.0f)),
      radians(std::make_unique<glm::vec3>(0.0f, 0.0f, 0.0f)),
      view(glm::mat4(1.0f)), proj(glm::mat4(1.0f))
{
    SetType(type);
}

Camera::~Camera()
{
}

void Camera::UpdateView()
{
    view = glm::translate(glm::mat4(1.0f), *translation) *
           glm::rotate(glm::mat4(1.0f), radians->x, glm::vec3(1, 0, 0)) *
           glm::rotate(glm::mat4(1.0f), radians->y, glm::vec3(0, 1, 0)) *
           glm::rotate(glm::mat4(1.0f), radians->z, glm::vec3(0, 0, 1));
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
