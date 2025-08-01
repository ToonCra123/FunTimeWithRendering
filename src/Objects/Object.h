//
// Created by micha on 8/1/2025.
//

#pragma once

#include "../Shader.h"
#include <glm/glm.hpp>

#include "../Light.h"
#include "glad/glad.h"

class Cube {
public:
	Cube(Shaders* mProgram, const glm::vec3 &color);
	~Cube();

	// void Update();
	void render(glm::mat4 &projection, glm::mat4 &view, glm::vec3 &camPos, float& timeval, Light& light);

private:

	glm::mat4 model{};

	Shaders* mProgram;

	glm::vec3 objectColor;
	GLuint VAO, VBO, EBO;

	unsigned int indeciesCount;
};

