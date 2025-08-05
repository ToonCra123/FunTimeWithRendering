//
// Created by micha on 8/4/2025.
//

#pragma once
#include <vector>
#include <glm/glm.hpp>

#include "../block/Blocks.h"

constexpr unsigned int CHUNK_SIZE = 16;
constexpr unsigned int CHUNK_HEIGHT = 128;


class ChunkBlockData {
public:
	ChunkBlockData();
	void Generate();

private:
	static BlockType GetBlockForPosition(int x, int y, int z);

	std::vector<BlockType> chunkBlocks;

	// Make a chunk pos class later
	// Also only going to be used for
	// World Gen Later
	glm::vec2 chunkPos;
};
