//
// Created by micha on 7/30/2025.
//

#include "Camera.h"

#include <glm/ext/matrix_transform.hpp>

#include "Input.h"
#include "GLFW/glfw3.h"


Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    : Position(position), WorldUp(up), Yaw(yaw), Pitch(pitch)
{
    UpdateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix() const {
    return glm::lookAt(Position, Position + Front, Up);
}

void Camera::Update() {
    if (Input::GetInstance()->GetKeyDown(GLFW_KEY_W)) {
        Position += Front;
    }
    if (Input::GetInstance()->GetKeyDown(GLFW_KEY_S)) {
        Position -= Front;
    }
}


void Camera::UpdateCameraVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);
    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up    = glm::normalize(glm::cross(Right, Front));
}
