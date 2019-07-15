#include "TextureMap.hpp"

TextureMap::TextureMap(Texture& texture, unsigned singleTextureSize)
	: _texture(texture), _singleTextureSize(singleTextureSize)
{
}

glm::vec2 TextureMap::getTextureCoords(unsigned row, unsigned column, Corner corner)
{
	glm::vec2 coords;

	int offsetX = 0, offsetY = 0;

	switch (corner)
	{
		case RightTop:
			offsetX = 1;
			break;
		case LeftBottom:
			offsetY = 1;
			break;
		case RightBottom:
			offsetX = 1;
			offsetY = 1;
			break;
	}

	coords.x = static_cast<float>(_singleTextureSize * (row + offsetX)) / _texture.getSize().x;
	coords.y = static_cast<float>(_singleTextureSize * (column + offsetY)) / _texture.getSize().y;

	return coords;
}

glm::vec2 TextureMap::getTextureCoords(Textures textureId, Corner corner)
{
	switch (textureId)
	{
		case Textures::Dirt:
			return getTextureCoords(0, 0, corner);
		case Textures::GrassSide:
			return getTextureCoords(1, 0, corner);
		case Textures::GrassTop:
			return getTextureCoords(2, 0, corner);
	}

	return getTextureCoords(15, 15, corner);
}
