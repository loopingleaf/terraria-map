#pragma once

#include "RessourceManager.h"
#include "Tile.h"

class GroundTile : public Tile
{
public:
	GroundTile(ResourceManager& resourceManager, const float& x, const float& y, const float& scale = 1.f)
	{
		m_texture = resourceManager.getTexture(Resources::GroundTexture);
		m_sprite = sf::Sprite(*m_texture);
		const sf::Vector2u textureSize = m_texture->getSize();
		m_sprite.setPosition(x * textureSize.x, y * textureSize.y);
		m_sprite.setScale(scale, scale);
	}
};
