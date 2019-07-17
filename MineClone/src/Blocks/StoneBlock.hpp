﻿#pragma once

#include "Block.hpp"

class StoneBlock : public Block
{
public:
	StoneBlock() noexcept;
	StoneBlock(const glm::vec3& pos) noexcept;

	std::array<Vertex, 4 * 6> getVertices(TextureMap& textureMap) override;
};