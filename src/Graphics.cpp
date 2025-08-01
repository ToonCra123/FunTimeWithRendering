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


Graphics::Graphics(GLFWwindow* window): camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f) {

    mWindow = window;
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cerr << "Failed to initialize GLAD\n";
        exit(-1);
    }

    sProgram = std::make_unique<Shaders>("../resources/shaders/vertex.glsl", "../resources/shaders/fragment.frag");

    // positions
    float vertices[] = {
        // positions            // normals

        // Front face
        -0.5f, -0.5f,  0.5f,     0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,     0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,

         // Back face
        -0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,

         // Left face
        -0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,

         // Right face
         0.5f, -0.5f, -0.5f,     1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,     1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,     1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,     1.0f,  0.0f,  0.0f,

         // Top face
        -0.5f,  0.5f, -0.5f,     0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,     0.0f,  1.0f,  0.0f,

         // Bottom face
        -0.5f, -0.5f, -0.5f,     0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,     0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f
     };

    unsigned int indices[] = {
        // front face
        0, 1, 2,
        2, 3, 0,

        // back face
        4, 5, 6,
        6, 7, 4,

        // left face
        8, 9,10,
       10,11, 8,

        // right face
       12,13,14,
       14,15,12,

        // top face
       16,17,18,
       18,19,16,

        // bottom face
       20,21,22,
       22,23,20
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), static_cast<void *>(nullptr));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void *>(3 * sizeof(float)));
    glEnableVertexAttribArray(1);



    glBindVertexArray(0);

    glEnable(GL_CULL_FACE);

    Input::SetLockCursor(true);
}

Graphics::~Graphics() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
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

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<float>(width)/height, 0.1f, 100.0f);

    unsigned int modelLoc = glGetUniformLocation(sProgram->GetProgram(), "model");
    unsigned int viewLoc = glGetUniformLocation(sProgram->GetProgram(), "view");
    unsigned int projLoc = glGetUniformLocation(sProgram->GetProgram(), "projection");

    glUseProgram(sProgram->GetProgram());


    glUniform1f(timeLocation, timeValue);


    // set light position (world space)
    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
    glUniform3fv(glGetUniformLocation(sProgram->GetProgram(), "lightPos"), 1, &lightPos[0]);

    // set light color and object color
    glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
    glm::vec3 objectColor(1.0f, 0.5f, 0.31f);
    glUniform3fv(glGetUniformLocation(sProgram->GetProgram(), "lightColor"), 1, &lightColor[0]);
    glUniform3fv(glGetUniformLocation(sProgram->GetProgram(), "objectColor"), 1, &objectColor[0]);

    // view position (camera pos)
    glm::vec3 viewPos = camera.Position;
    glUniform3fv(glGetUniformLocation(sProgram->GetProgram(), "viewPos"), 1, &viewPos[0]);


    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}
