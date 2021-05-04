#pragma once

#include <memory>
#include <string>
#include <vector>
#include "Region.h"

class Map
{
public:

	/// <summary>
	/// Creates a map. The regions may be built later.
	/// </summary>
	/// <param name="width">Number of regions in latitude</param>
	/// <param name="height">Number of regions in longitude</param>
	/// <param name="regionSize">Number of tiles in a region row. Regions are square for now</param>
	Map(const int& width, const int& height, const int& regionSize = 32)
		: m_width(width), m_height(height), m_regionSize(regionSize)
	{
		m_regions.resize(m_width * m_height);
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
		//std::cout << m_regions[x * m_width + y]->toString() << std::endl;
		return m_regions[x * m_height + y];
	}

	void addRegion(const Region& region, const int& x, const int& y)
	{
		std::cout << x << "; " << y << std::endl;
		m_regions[x * m_height + y] = std::make_shared<Region>(region);
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
	std::vector<std::shared_ptr<Region>> m_regions;
};
