#pragma once
#ifndef REGION_H
#define REGION_H

#include <vector>
#include <memory>
#include "Tile.h"

class Region
{
public:
	explicit Region(const int& width, const int& height)
		: m_width(width), m_height(height)
	{
		m_tiles.resize(width);
		for(auto &line : m_tiles)
		{
			line.resize(height);
		}
	}

	void addTile(const Tile& tile, const int& x, const int& y)
	{

	}

private:
	int m_width;
	int m_height;
	std::vector<std::vector<std::shared_ptr<Tile>>> m_tiles;
};

#endif
