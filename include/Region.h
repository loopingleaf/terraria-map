#pragma once

#include <vector>
#include "Tile.h"

class Region
{
public:
	Region() = default;
	
	explicit Region(const int& width, const int& height)
		: m_width(width), m_height(height)
	{
		m_tiles.resize(m_width * m_height);
	}

	void addTile(const Tile& tile, const int& x, const int& y)
	{
		m_tiles[x * m_height + y] = tile;
	}

	Tile& getTile(const int& x, const int& y)
	{
		return m_tiles[x * m_height + y];
	}

	int getWidth() const
	{
		return m_width;
	}

	int getHeight() const
	{
		return m_height;
	}

	sf::Vector2f getCoordinates() const
	{
		return m_coords;
	}

private:
	int m_width;
	int m_height;
	sf::Vector2f m_coords;
	std::vector<Tile> m_tiles;
};
