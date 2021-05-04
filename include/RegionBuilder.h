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

	virtual void build(Region& region, const int& x, const int& y) = 0;

protected:
	std::shared_ptr<ResourceManager> m_resourceManager;
};
