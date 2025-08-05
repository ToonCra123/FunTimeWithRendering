//
// Created by micha on 8/4/2025.
//

#pragma once
#include "Chunk.h"
#include "../../Light.h"
#include "glad/glad.h"
#include "../../Shader.h"

class ChunkRenderer {
public:
	ChunkRenderer(Shaders* mProgram);

	void GenerateMesh(ChunkBlockData &data);

	void render(glm::mat4 &projection, glm::mat4 &view, Light &light);

private:

	glm::mat4 model;

	Shaders* mProgram;

	GLuint VAO, VBO, EBO;

	unsigned int indeciesCount;
};
