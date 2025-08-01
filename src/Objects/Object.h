//
// Created by micha on 8/1/2025.
//

#pragma once

#include "../Shader.h"
#include <glm/glm.hpp>

#include "glad/glad.h"

class Cube {
public:
	Cube(const Shaders &mProgram, const glm::vec3 &color);
	~Cube();

	// void Update();
	void render();

private:

	glm::mat4 model;

	Shaders mProgram;

	glm::vec3 objectColor;
	GLuint VAO, VBO, EBO;
};

