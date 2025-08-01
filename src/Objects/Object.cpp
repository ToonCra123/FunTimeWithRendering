//
// Created by micha on 8/1/2025.
//

#include "Object.h"

#include <glm/gtc/type_ptr.hpp>


Cube::Cube(Shaders* mProgram, const glm::vec3 &color) : mProgram(mProgram), objectColor(color) {
	   VAO = VBO = EBO = 0;

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
    indeciesCount = sizeof(indices) / sizeof(unsigned int);


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


    model = glm::mat4(1.0f);
}



Cube::~Cube() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Cube::render(glm::mat4 &projection, glm::mat4 &view, glm::vec3 &camPos, float& timeval, Light& light) {
    unsigned int timeLocation = glGetUniformLocation(mProgram->GetProgram(), "u_time");

    unsigned int modelLoc = glGetUniformLocation(mProgram->GetProgram(), "model");
    unsigned int viewLoc = glGetUniformLocation(mProgram->GetProgram(), "view");
    unsigned int projLoc = glGetUniformLocation(mProgram->GetProgram(), "projection");

    glUseProgram(mProgram->GetProgram());


    glUniform1f(timeLocation, timeval);


    // set light position (world space)
    glUniform3fv(glGetUniformLocation(mProgram->GetProgram(), "lightPos"), 1, &light.position[0]);

    // set light color and object color
    glUniform3fv(glGetUniformLocation(mProgram->GetProgram(), "lightColor"), 1, &light.color[0]);
    glUniform3fv(glGetUniformLocation(mProgram->GetProgram(), "objectColor"), 1, &objectColor[0]);

    // view position (camera pos)
    glm::vec3 viewPos = camPos;
    glUniform3fv(glGetUniformLocation(mProgram->GetProgram(), "viewPos"), 1, &viewPos[0]);

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indeciesCount, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}
