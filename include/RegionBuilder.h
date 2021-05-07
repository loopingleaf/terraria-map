#pragma once

#include "Region.h"
#include "RessourceManager.h"

class RegionBuilder
{
public:
	explicit RegionBuilder(std::shared_ptr<ResourceManager>& resourceManager)
		: m_resourceManager(std::move(resourceManager))
	{}
	
	virtual ~RegionBuilder() = default;

	/// <summary>
	/// Build the tiles in the given region using the noise at the given coordinates.
	/// </summary>
	/// <param name="region">The region to build</param>
	/// <param name="noiseX">The x coords starting point of the noise</param>
	/// <param name="noiseY">The y coords starting point of the noise</param>
	virtual void build(Region& region, const int& noiseX, const int& noiseY) = 0;

protected:
	std::shared_ptr<ResourceManager> m_resourceManager;
	static const float DEFAULT_SCALE;
};

const float RegionBuilder::DEFAULT_SCALE = 2.f;
