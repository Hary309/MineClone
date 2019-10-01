#include "ChunkManager.hpp"

#include <algorithm>

#include "World.hpp"

ChunkManager::ChunkManager(World& world)
	: _world(world)
{
}

ChunkManager::~ChunkManager()
{
}

Chunk* ChunkManager::getChunk(const coords::ChunkPos& chunkPos) const
{
	auto it = std::find_if(_chunks.begin(), _chunks.end(), [&](auto& it) { return it->getChunkPos() == chunkPos; });

	if (it != _chunks.end())
	{
		return (*it).get();
	}

	return nullptr;
}

ChunkSegment* ChunkManager::getChunkSegment(const coords::ChunkSegmentPos& chunkSegmentPos) const
{
	auto chunk = getChunk(coords::ChunkPos { chunkSegmentPos.x, chunkSegmentPos.z });

	if (chunk == nullptr)
		return nullptr;

	return chunk->getChunkSegment(chunkSegmentPos.y);
}

void ChunkManager::addChunk(const coords::ChunkPos& chunkPos, FastNoise& noise, TextureAtlas& textureAtlas)
{
	_chunks.push_back(std::make_unique<Chunk>(_world, chunkPos, noise, textureAtlas));
}

void ChunkManager::updateMesh(TextureAtlas& textureAtlas)
{
	for (auto& chunk : _chunks)
	{
		chunk->generateMesh(textureAtlas);
	}
}

void ChunkManager::drawChunks(ShaderProgram& shaderProgram)
{
	auto& frustumView = _world.getFrustumView();

	for (auto& chunk : _chunks)
	{
		auto posXYZ = coords::WorldPos { chunk->getChunkPos().x * ChunkSegment::Size, 0, chunk->getChunkPos().y * ChunkSegment::Size };

		if (frustumView.isBoxInFOV(posXYZ, glm::ivec3 { ChunkSegment::Size, 0, ChunkSegment::Size }))
		{
			chunk->drawChunks(shaderProgram);
		}
	}
}

void ChunkManager::drawGrid(ShaderProgram& shaderProgram)
{
	for (auto& chunk : _chunks)
	{
		chunk->drawGrid(shaderProgram);
	}
}
