#pragma once

#include <vector>
#include <memory>
#include "Tile.h"

class Region
{
public:
	explicit Region(const int& width, const int& height)
		: m_width(width), m_height(height)
	{
		m_tiles.resize(m_width * m_height);
	}

	/*void addTile(const Tile& tile, const int& x, const int& y)
	{
		m_tiles[x + (y * m_height)] = std::make_shared<Tile>(tile);
	}*/

	void addTile(std::shared_ptr<Tile>& tile, const int& x, const int& y)
	{
		m_tiles[x * m_height + y] = std::move(tile);
	}

	Tile& getTile(const int& x, const int& y)
	{
		return *m_tiles[x * m_height + y];
	}

	int getWidth() const
	{
		return m_width;
	}

	int getHeight() const
	{
		return m_height;
	}

	std::string toString()
	{
		std::string retval;
		for(int i = 0; i < m_height; ++i)
		{
			for(int j = 0; j < m_width; ++j)
			{
				retval += getTile(j, i).toString();
			}
			retval += "\n";
		}
		return retval;
	}

private:
	int m_width;
	int m_height;
	std::vector<std::shared_ptr<Tile>> m_tiles;
};
