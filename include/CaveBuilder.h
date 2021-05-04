#pragma once

#include "Noise2D.h"
#include "RegionBuilder.h"

class CaveBuilder : public RegionBuilder
{
public:
#pragma region ctor
	CaveBuilder() = delete;

	//CaveBuilder(std::shared_ptr<Noise2D<int>> noise)
#pragma endregion
	
	void build(Region& region, const int& x, const int& y) override
	{
		
	}

private:
	std::shared_ptr<Noise2D<int>> m_noiseModule;
	double m_step;
};
