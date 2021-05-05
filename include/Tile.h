#pragma once

#include <memory>

#include "sfml/Graphics.hpp"

class Tile
{
public:
	Tile() = default;
	
	explicit Tile(const std::shared_ptr<sf::Texture>& texture, const float& x, const float& y)
		: m_texture(texture)
	{
		m_sprite = sf::Sprite(*m_texture);
		m_sprite.setPosition(x, y);
		m_sprite.setScale(2.f, 2.f);
	}

	virtual ~Tile() = default;

	sf::Sprite& getSprite()
	{
		return m_sprite;
	}

protected:
	std::shared_ptr<sf::Texture> m_texture;
	sf::Sprite m_sprite;
};
