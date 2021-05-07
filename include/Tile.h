#pragma once

#include <memory>

#include "sfml/Graphics.hpp"

class Tile
{
public:
	Tile() = default;
	
	//explicit Tile(ResourceManager& resourceManager, const float& x, const float& y);

	virtual ~Tile() = default;

	sf::Sprite& getSprite()
	{
		return m_sprite;
	}

protected:
	std::shared_ptr<sf::Texture> m_texture;
	sf::Sprite m_sprite;
};
