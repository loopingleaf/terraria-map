#pragma once
#ifndef GROUND_GENERATOR_H
#define GROUND_GENERATOR_H

#include <iostream>
#include <memory>
#include <algorithm>

#include "noise/noise.h"
#include "Region.h"

namespace ns = noise;

/// Builds the surface in a region.
class SurfaceBuilder
{
public:
#pragma region ctor
	SurfaceBuilder() = delete;
	
	/*explicit SurfaceBuilder(const int& seed, const double& frequency = 1.0, const int& octaves = 2)
	{
		//m_noiseLine = std::make_shared<ns::module::Perlin>();
		m_noiseLine->SetSeed(seed);
		m_noiseLine->SetFrequency(frequency);
		m_noiseLine->SetOctaveCount(octaves);
	}*/

	explicit SurfaceBuilder(std::shared_ptr<ns::module::Perlin>& noiseModule, const double& step,
		const double& surfaceIndex = 0.)
		: m_noiseModule(noiseModule), m_step(step), m_surfaceOffset(surfaceIndex)
	{
		m_noiseLine.SetAttenuate(false);
		m_noiseLine.SetModule(*m_noiseModule);
	}

	SurfaceBuilder(const SurfaceBuilder& sb)
		: m_noiseModule(sb.m_noiseModule), m_step(sb.m_step), m_surfaceOffset(sb.m_surfaceOffset)
	{
		m_noiseLine.SetAttenuate(sb.m_noiseLine.GetAttenuate());
		m_noiseLine.SetModule(*m_noiseModule);
	}
	
	/*SurfaceBuilder(SurfaceBuilder&& sb) noexcept
	{
		m_noiseLine = std::move(sb.m_noiseLine);
		m_step = std::exchange(sb.m_step, 0.);
		m_surfaceOffset = std::exchange(sb.m_surfaceOffset, 0.);
	}*/

	SurfaceBuilder& operator=(const SurfaceBuilder& sb)
	{
		if(this == &sb)
			return *this;

		m_noiseLine = sb.m_noiseLine;
		m_step = sb.m_step;
		m_surfaceOffset = sb.m_surfaceOffset;
		return *this;
	}

	/*SurfaceBuilder& operator=(SurfaceBuilder&& sb) noexcept
	{
		m_noiseLine = std::move(sb.m_noiseLine);
		m_step =
		return *this;
	}*/

	~SurfaceBuilder() = default;
#pragma endregion

	/// <summary>
	/// Build the tiles in the given region using the Perlin noise module
	/// at the given coordinates
	/// </summary>
	/// <param name="region">The region to build</param>
	/// <param name="x"> The x coords starting point of the Perlin noise</param>
	void build(Region& region, const int& x)
	{
		// We set the segment of the m_noiseLine
		const auto startPoint = x * m_step;
		const auto endPoint = (static_cast<double>(x) + region.getWidth()) * m_step;
		m_noiseLine.SetStartPoint(startPoint, 0., 0.);
		m_noiseLine.SetEndPoint(endPoint, 0., 0.);
#ifdef _DEBUG
		std::cout << "Building a surface inside a region..." << std::endl;
#endif

		for(int i = 0; i < region.getWidth(); ++i)
		{
			const double perlinValue = m_noiseLine.GetValue(static_cast<double>(i) / region.getWidth());
			const double elevation = region.getHeight() * ((perlinValue + 1) / 2);
			const int clampedElevation = std::clamp(static_cast<int>(elevation), 0, region.getHeight());
			/*if(clampedElevation == 0)
				continue;*/

			for(int j = 0; j < region.getHeight(); ++j)
			{
				if(j >= region.getHeight() - clampedElevation)
				{
					std::shared_ptr<Tile> newTile = std::make_shared<Tile>(GroundType::Dirt);
					region.addTile(newTile, i, j);
				}
				else
				{
					std::shared_ptr<Tile> newTile = std::make_shared<Tile>(GroundType::None);
					region.addTile(newTile, i, j);
				}
			}
		}
#ifdef _DEBUG
		std::cout << region.toString() << std::endl;
#endif
	}

private:
	std::shared_ptr<ns::module::Module> m_noiseModule;
	ns::model::Line m_noiseLine;
	double m_step;
	double m_surfaceOffset;
};

#endif
