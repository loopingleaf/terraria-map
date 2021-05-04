#pragma once

#include <memory>

#include "sfml/Graphics.hpp"

class Tile
{
public:
	Tile() = default;
	
	explicit Tile(std::shared_ptr<sf::Texture> texture)
		: m_texture(texture)
	{}

	virtual ~Tile() = default;

protected:
	std::shared_ptr<sf::Texture> m_texture;
	sf::Sprite m_sprite;
};
