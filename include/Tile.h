#ifndef TILE_H
#define TILE_H
#pragma once

#include <memory>
//#include "SFML/Graphics.h"

enum GroundType
{
	None,
	Dirt,
	Rock
};

class Tile
{
public:
	explicit Tile(GroundType type)
		: m_type(type)
	{}

	std::string toString()
	{
		switch (m_type)
		{
		case GroundType::None:
			return ".";
		case GroundType::Dirt:
			return  "x";
		case GroundType::Rock:
			return "X";
		default:
			return " ";
		}
	}

	GroundType& getType()
	{
		return m_type;
	}

private:
	GroundType m_type;
	//std::shared_ptr<> m_sprite;
};

#endif
