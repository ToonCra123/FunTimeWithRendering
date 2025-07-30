//
// Created by micha on 7/29/2025.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Graphics.h"


Graphics::Graphics(GLFWwindow* window) {


    mWindow = window;
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cerr << "Failed to initialize GLAD\n";
        exit(-1);
    }

    sProgram = std::make_unique<Shaders>("../resources/shaders/vertex.glsl", "../resources/shaders/fragment.glsl");

    float vertices[] = {
        // positions        // tex coords (optional)
        -1.0f,  1.0f, 0.0f,  // top-left
        -1.0f, -1.0f, 0.0f,  // bottom-left
         1.0f, -1.0f, 0.0f,  // bottom-right
         1.0f,  1.0f, 0.0f   // top-right
    };

    unsigned int indices[] = {
        0, 1, 2,   // first triangle
        0, 2, 3    // second triangle
    };


    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

Graphics::~Graphics() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Graphics::DoFrame() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw
    // Get uniform location once (after linking shaders)
    GLint timeLocation = glGetUniformLocation(sProgram->GetProgram(), "u_time");

    // In your render loop, update the uniform every frame
    float timeValue = (float)glfwGetTime(); // GLFW returns time in seconds since init

    glUseProgram(sProgram->GetProgram());
    glUniform1f(timeLocation, timeValue);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}
