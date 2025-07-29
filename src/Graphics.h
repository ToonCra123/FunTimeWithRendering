//
// Created by micha on 7/29/2025.
//

#pragma once
#include <memory>

#include "Shader.h"
#include "GLFW/glfw3.h"

class Graphics {
public:
    Graphics(GLFWwindow* window);
    ~Graphics();
    void DoFrame();
private:
    GLFWwindow* mWindow;
    unsigned int VAO, VBO;
    std::unique_ptr<Shaders> sProgram;
};
