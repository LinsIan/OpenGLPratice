#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <string>

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
    float moveSpeed;
    float sensitivity;
    float pitch;
    float yaw;
    float fov;
    glm::mat4 view;
    glm::mat4 proj;

    std::unique_ptr<glm::vec3> position;
    std::unique_ptr<glm::vec3> forward;
    std::unique_ptr<glm::vec3> up;

    void UpdateView();

public:
    Camera(CameraType type, float screenWidth, float screenHeight); 
    ~Camera();

    void SetType(CameraType newType);
    void MoveForward();
    void MoveBackward();
    void MoveLeft();
    void MoveRight();
    void Rotate(float xOffset, float yOffset);
	void SetFov(float newFov);

    inline const glm::mat4& GetViewMatrix() { UpdateView(); return view; }
    inline const glm::mat4& GetProjectionMatrix() const { return proj; }
	inline const std::string GetCameraTypeString() const
	{
		return type == PERSPECTIVE ? "Perspective" : "Orthographic";
	}

    glm::vec3& GetPosition() { return *position; }
    glm::vec3& GetForward() { return *forward; }
    CameraType GetCameraType() const { return type; }
};
