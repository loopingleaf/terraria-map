#ifndef TILE_H
#define TILE_H
#pragma once

#include <memory>
#include "SFML/Graphics.h"

enum GroundType
{
	None,
	Dirt,
	Rock
};

class Tile
{
public:
	explicit Tile(const GroundType &type)
		: m_type(type)
	{}


private:
	GroundType m_type;
	//std::shared_ptr<> m_sprite;
};

#endif
