//
// Created by micha on 8/4/2025.
//

#include "ChunkRenderer.h"

ChunkRenderer::ChunkRenderer(Shaders* program) {
	mProgram = program;
	VBO = VAO = EBO = 0;
	model = glm::mat4(1.0f);
}


void ChunkRenderer::GenerateMesh(ChunkBlockData &data) {
	std::vector<float> vertices;
	std::vector<unsigned int> indices;





	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices, GL_STATIC_DRAW);

	// position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), static_cast<void *>(nullptr));
	glEnableVertexAttribArray(0);


	// normals
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void *>(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);


}

void ChunkRenderer::render(glm::mat4 &projection, glm::mat4 &view, Light &light) {
	// shit
}
