#pragma once

#include <iostream>
#include <memory>

#include "GroundTile.h"
#include "Noise2D.h"
#include "noise/noise.h"
#include "RegionBuilder.h"
#include "Region.h"

namespace ns = noise;

/// Builds the surface in a region.
class SurfaceBuilder : public RegionBuilder
{
public:
#pragma region ctor
	SurfaceBuilder() = delete;

	explicit SurfaceBuilder(std::shared_ptr<ResourceManager> resourceManager, Noise2D<int> noise, const double& step, const double& surfaceIndex = 0.)
		: RegionBuilder(resourceManager), m_noise(noise), m_step(step), m_surfaceOffset(surfaceIndex)
	{}

	SurfaceBuilder& operator=(const SurfaceBuilder& sb)
	{
		if(this == &sb)
			return *this;

		m_resourceManager = sb.m_resourceManager;
		m_noise = sb.m_noise;
		m_step = sb.m_step;
		m_surfaceOffset = sb.m_surfaceOffset;
		return *this;
	}
#pragma endregion

	/// <summary>
	/// Build the tiles in the given region using the Perlin noise module
	/// at the given coordinates.
	/// </summary>
	/// <param name="region">The region to build</param>
	/// <param name="x"> The x coords starting point of the Perlin noise</param>
	void build(Region& region, const int& x, const int& y) override
	{
#ifdef _DEBUG
		std::cout << "Building a surface inside a region..." << std::endl;
#endif

		Noise2D<int> perlin = Noise2D<int>(156112, 0, region.getHeight(), 1.f, 2,
			1.f, 3.f);
		
		for(int i = 0; i < region.getWidth(); ++i)
		{
			const int clampedElevation = perlin.getValue1D(static_cast<float>(i * m_step + x * m_step));
			for(int j = 0; j < region.getHeight(); ++j)
			{
				if(j >= region.getHeight() - clampedElevation)
				{
					Tile groundTile = GroundTile(*m_resourceManager, i * DEFAULT_SCALE, j * DEFAULT_SCALE, DEFAULT_SCALE);
					region.addTile(groundTile, i, j);
				}
			}
		}
	}

private:
	Noise2D<int> m_noise;
	double m_step;
	double m_surfaceOffset;
};
