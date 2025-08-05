//
// Created by micha on 7/30/2025.
//

#pragma once
#include <glm/glm.hpp>
#include <glm/fwd.hpp>

class Camera {
public:
    Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch);

    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;

    glm::mat4 GetViewMatrix() const;

    void Update(double deltaTime);
private:
    float Yaw;
    float Pitch;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    bool locked = true;

    void UpdateCameraVectors();
};
