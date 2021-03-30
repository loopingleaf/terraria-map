#ifndef MAP_H
#define MAP_H
#pragma once

#include <memory>
#include <vector>
#include "Region.h"

class Map
{
public:
	Map(const int& width, const int& height, const int& regionSize = 32)
		: m_width(width), m_height(height), m_regionSize(regionSize)
	{
		m_regions.resize(regionSize);
		for(auto &line : m_regions)
		{
			line.resize(regionSize);
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

	std::shared_ptr<Region> getRegion(const int& x, const int& y)
	{
		return m_regions[x][y];
	}

	void addRegion(const Region& region, const int& x, const int& y)
	{
		m_regions[x][y] = std::make_shared<Region>(region);
	}

private:
	/// Number of region columns in m_regions
	int m_width;

	/// Number of region rows in m_regions
	int m_height;

	/// Size of each regions, in number of tiles
	int m_regionSize;

	/// List of region in the map.
	/// m_regions[column][row] (column being the horizontal index and row the vertical index)
	std::vector<std::vector<std::shared_ptr<Region>>> m_regions = std::vector<std::vector<std::shared_ptr<Region>>>();
};

#endif
