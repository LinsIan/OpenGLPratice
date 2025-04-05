#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

enum CameraType
{
    PERSPECTIVE,
    ORTHOGRAPHIC
};

class Camera
{
private:
    CameraType type;
    float screenWidth;
    float screenHeight;
    glm::mat4 view;
    glm::mat4 proj;

    std::unique_ptr<glm::vec3> translation;
    std::unique_ptr<glm::vec3> radians;

    void UpdateView();

public:
    Camera(CameraType type = PERSPECTIVE, float screenWidth, float screenHeight); 
    ~Camera();

    void SetType(CameraType newType);

    inline const glm::mat4& GetViewMatrix() { UpdateView(); return view; }
    inline const glm::mat4& GetProjectionMatrix() const { return proj; }

    glm::vec3& GetTranslation() { return *translation; }
    glm::vec3& GetRotation() { return *radians; }
};
