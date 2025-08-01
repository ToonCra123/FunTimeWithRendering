//
// Created by micha on 7/29/2025.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Graphics.h"

#include "Input.h"
#include "Light.h"
#include "Objects/Object.h"

struct Light;
std::unique_ptr<Cube> cube;
std::unique_ptr<Light> light;


Graphics::Graphics(GLFWwindow* window): camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f) {

    mWindow = window;
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cerr << "Failed to initialize GLAD\n";
        exit(-1);
    }

    sProgram = std::make_unique<Shaders>("../resources/shaders/vertex.glsl", "../resources/shaders/fragment.frag");

    cube = std::make_unique<Cube>(sProgram.get(), glm::vec3(0.1f, 0.5f, 0.7f));
    light = std::make_unique<Light>();
    light->color = glm::vec3(1.0f, 1.0f, 1.0f);
    light->position = glm::vec3(1.2f, 1.0f, 2.0f);

    glEnable(GL_CULL_FACE);

    Input::SetLockCursor(true);
}

Graphics::~Graphics() {
}

float deltaTime = 0.0f;
float lastFrame = 0.0f;

void Graphics::DoFrame() {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    camera.Update(deltaTime);

    int width, height;
    glfwGetFramebufferSize(mWindow, &width, &height);

    glViewport(0, 0, width, height);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw
    // Get uniform location once (after linking shaders)
    GLint timeLocation = glGetUniformLocation(sProgram->GetProgram(), "u_time");

    // In your render loop, update the uniform every frame
    float timeValue = static_cast<float>(glfwGetTime()); // GLFW returns time in seconds since init

    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<float>(width)/height, 0.1f, 100.0f);

    cube->render(projection, view, camera.Position, timeValue, *(light));
}
