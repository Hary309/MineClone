#include "Block.hpp"

#include "Chunk.hpp"

Block::Block(Chunk& chunk, const glm::ivec3& pos, Blocks blockType) noexcept
	: 
	_chunk(chunk),
	_pos(pos),
	_blockType(blockType)
{
}

Block::Block(const Block& other) noexcept
	:
	_chunk(other._chunk),
	_pos(other._pos),
	_blockType(other._blockType)
{

}

Block& Block::operator=(const Block& other) noexcept
{
	_pos = other._pos;
	_blockType = other._blockType;

	return *this;
}

Block::Block(Block&& other) noexcept
	:
	_chunk(other._chunk),
	_pos(std::move(other._pos)),
	_blockType(std::move(other._blockType))
{

}

Block& Block::operator=(Block&& other) noexcept
{
	_pos = std::move(other._pos);
	_blockType = std::move(other._blockType);

	return *this;
}

Block* Block::getNeighbor(BlockSide side) const
{
	return _chunk.getNeighbourOfBlock(this, side);
}
