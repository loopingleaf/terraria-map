#pragma once

#include "sfml/Graphics.hpp"

enum class Resources : unsigned int
{
	GroundTexture = 0,
	RockTexture = 1
};

struct ResourceManager
{
	ResourceManager(const std::string& resourcesPath)
	{
		m_textures.reserve(2);
		auto gt = std::make_shared<sf::Texture>();
		gt->loadFromFile(resourcesPath + "/ground.png");
		m_textures.push_back(gt);
		auto rt = std::make_shared<sf::Texture>();
		rt->loadFromFile(resourcesPath + "/rock.png");
		m_textures.push_back(rt);
	}

	std::shared_ptr<sf::Texture>& getTexture(Resources r)
	{
		return m_textures[static_cast<unsigned int>(r)];
	}
private:
	std::vector<std::shared_ptr<sf::Texture>> m_textures;
};
