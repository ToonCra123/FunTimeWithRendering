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

const float speed = 2.5f;
const float sensitivity = 0.1f;
double lastX = 0.0, lastY = 0.0;
bool firstMouse = true;

// Basic Camera Controlls
void Camera::Update(double deltaTime) {
    if (Input::GetInstance()->GetKeyDown(GLFW_KEY_W)) {
        Position += Front * speed * static_cast<float>(deltaTime);
    }
    if (Input::GetInstance()->GetKeyDown(GLFW_KEY_S)) {
        Position -= Front * speed * static_cast<float>(deltaTime);
    }
    if (Input::GetInstance()->GetKeyDown(GLFW_KEY_D)) {
        Position += Right * speed * static_cast<float>(deltaTime);
    }
    if (Input::GetInstance()->GetKeyDown(GLFW_KEY_A)) {
        Position -= Right * speed * static_cast<float>(deltaTime);
    }
    if (Input::GetInstance()->GetKeyDown(GLFW_KEY_SPACE)) {
        Position += glm::vec3(0.0f, 1.0f, 0.0f) * speed * static_cast<float>(deltaTime);
    }
    if (Input::GetInstance()->GetKeyDown(GLFW_KEY_LEFT_SHIFT)) {
        Position += glm::vec3(0.0f, -1.0f, 0.0f) * speed * static_cast<float>(deltaTime);
    }

    if (Input::GetInstance()->GetKeyDown(GLFW_KEY_ESCAPE) && locked) {
        locked = false;
        Input::SetLockCursor(false);
    }

    // Mouse Controls
    double x, y;
    Input::GetCursorPos(x, y);

    if (firstMouse) {
        lastX = x;
        lastY = y;
        firstMouse = false;
    }

    double offsetX = x - lastX;
    double offsetY = lastY - y; // reversed: y-coordinates go down

    lastX = x;
    lastY = y;

    offsetX *= sensitivity;
    offsetY *= sensitivity;

    Yaw   += static_cast<float>(offsetX);
    Pitch += static_cast<float>(offsetY);

    UpdateCameraVectors();

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
