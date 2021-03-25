#pragma once
#ifndef GROUND_GENERATOR_H
#define GROUND_GENERATOR_H

#include <vector>
#include <memory>

#include "Map.h"
#include "noise/noise.h"

namespace ns = noise;

class GroundBuilder
{
	const int DEFAULT_SIZE = 256;

public:
	GroundBuilder() = default;
	
	explicit GroundBuilder(const int& seed, const double& frequency = 1.0, const int& octaves = 2)
	{
		m_perlin = std::make_shared<ns::module::Perlin>();
		m_perlin->SetSeed(seed);
		m_perlin->SetFrequency(frequency);
		m_perlin->SetOctaveCount(octaves);
	}

	~GroundBuilder() = default;

	Map build(Map &map)
	{
		for(auto i = 0; i < map.getWidth(); ++i)
		{
			for(auto j = 0; j < map.getHeight(); ++j)
			{
				// TODO
			}
		}
		return map;
	}

	Map build()
	{
		Map retval = Map(DEFAULT_SIZE, DEFAULT_SIZE);
		return build(retval);
	}

private:
	std::shared_ptr<ns::module::Perlin> m_perlin;
};

#endif
