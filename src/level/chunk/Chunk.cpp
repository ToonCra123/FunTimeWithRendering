//
// Created by micha on 8/4/2025.
//

#include "Chunk.h"

ChunkBlockData::ChunkBlockData() {
	chunkPos = glm::vec2(0, 0);
};

void ChunkBlockData::Generate() {
	chunkBlocks.clear();
	for (int y = 0; y < CHUNK_HEIGHT; y++) {
		for (int x = 0; x < CHUNK_SIZE; x++) {
			for (int z = 0; z < CHUNK_SIZE; z++) {
				chunkBlocks.push_back(GetBlockForPosition(x, y, z));
			}
		}
	}
}

BlockType ChunkBlockData::GetBlockForPosition(int x, int y, int z) {
	if (y <= 4) {
		return DIRT;
	}
	else return AIR;
}
