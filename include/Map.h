#ifndef MAP_H
#define MAP_H
#pragma once

#include <memory>
#include <vector>
#include "Tile.h"

class Map
{
public:
	Map(const int& width, const int& height)
		: m_width(width), m_height(height)
	{
		m_tiles.resize(width);
		for(auto &line : m_tiles)
		{
			line.resize(height);
		}
	}
	
	int getWidth() const
	{
		return m_width;
	}

	int getHeight() const
	{
		return  m_height;
	}

	std::shared_ptr<Tile> getTile(const int& x, const int& y)
	{
		return m_tiles[x][y];
	}

	void addTile(const Tile& tile, const int& x, const int& y)
	{
		m_tiles[x][y] = std::make_shared<Tile>(tile);
	}

private:
	int m_width;
	int m_height;
	std::vector<std::vector<std::shared_ptr<Tile>>> m_tiles;
};

#endif
