#pragma once
#ifndef GROUND_GENERATOR_H
#define GROUND_GENERATOR_H

#include <iostream>
#include <memory>

#include "noise/noise.h"
#include "Region.h"

namespace ns = noise;

const double MIN_NOISE_VALUE = -1.;

/// Builds the surface.
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

	explicit SurfaceBuilder(std::shared_ptr<ns::model::Line>& noiseLine, const double& step,
		const double& surfaceIndex = 0.)
		: m_noiseLine(noiseLine), m_step(step), m_surfaceOffset(surfaceIndex)
	{}

	SurfaceBuilder(const SurfaceBuilder& sb)
		: m_noiseLine(sb.m_noiseLine), m_step(sb.m_step), m_surfaceOffset(sb.m_surfaceOffset)
	{}
	
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
	
	/// Build the tiles in the given region using the Perlin noise module
	/// at the given coordinates
	/// 
	/// @param region The region to build
	/// @param x The x coords starting point of the Perlin noise
	void build(Region& region, const int& x)
	{
		m_noiseLine->SetStartPoint(x, 0., 0.);
		m_noiseLine->SetEndPoint(x + region.getWidth(), 0., 0.);
		for(auto i = 0; i < region.getWidth(); ++i)
		{
			const int column = x + i;
			const double surfaceIndex = (m_noiseLine->GetValue(static_cast<double>(column) * m_step) - MIN_NOISE_VALUE) / 2;
			const int stopAt = static_cast<int>(std::round(region.getHeight() * surfaceIndex));
			std::cout << stopAt << "; ";
			std::cout << std::endl;
			/*for(auto j = region.getHeight() - 1; j <= ; --j)
			{
				//std::cout << m_noiseLine->GetValue(x + i * 0.001, y + 0.001, 0.001) << "; ";
			}*/
		}
	}

private:
	std::shared_ptr<ns::model::Line> m_noiseLine;
	double m_step;
	double m_surfaceOffset;
};

#endif
