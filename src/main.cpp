#include <iostream>
#include <cmath>

#include "Noise2D.h"
#include "Map.h"
#include "SurfaceBuilder.h"
#include "sfml/Graphics.hpp"
#include "noise/noise.h"

namespace ns = noise;

static void initArray(sf::Uint8* pixels, int width, int height)
{
    for (int j = 0; j < height; ++j)
    {
        for (int i = 0; i < width; ++i)
        {
            pixels[4 * (j * width + i)] = 255;
            pixels[4 * (j * width + i) + 1] = 0;
            pixels[4 * (j * width + i) + 2] = 0;
            pixels[4 * (j * width + i) + 3] = 255;
        }
    }
}

// Fonction qui permet de change un pixel, en lui affectant une couleur RGB, on lui laisse sa transparence à 255 (donc sans transparence).
static void writeColor(sf::Uint8* pixels, int x, int y, int width, sf::Vector3<sf::Uint8> color)
{
    pixels[4 * (y * width + x)] = color.x;
    pixels[4 * (y * width + x) + 1] = color.y;
    pixels[4 * (y * width + x) + 2] =  color.z;
    pixels[4 * (y * width + x) + 3] = 255;
}

static void perlinToArray(sf::Uint8* arrayOut, Noise2D<int>& perlin, const unsigned int& width, const unsigned int& height)
{
	for(unsigned int x = 0; x < width; ++x)
	{
		for(unsigned int y = 0; y < height; ++y)
		{
			int val = perlin.getValue(static_cast<float>(x) * 0.05f, static_cast<float>(y) * 0.05f);
			//std::cout << val << std::endl;
			writeColor(arrayOut, x, y, width, sf::Vector3<sf::Uint8>(val, val, val));
		}
	}
}

int main()
{
	Noise2D<int> perlin = Noise2D<int>(156112, 0, 16, 1.f, 2,
			1.f, 3.f);
	auto line = std::make_shared<ns::model::Line>();
	std::shared_ptr<ResourceManager> rm = std::make_shared<ResourceManager>("data/images/");
	SurfaceBuilder sb(std::move(rm), perlin, 0.04);
	
	Map map(4, 1);
	
	/*sb.build(region, 0);
	sb.build(region, 1);
	sb.build(region, 2);
	sb.build(region, 3);
	sb.build(region, 4);
	sb.build(region, 5);
	sb.build(region, 6);
	sb.build(region, 7);
	sb.build(region, 8);
	sb.build(region, 9);
	sb.build(region, 10);*/

	Region region1(16, 16);
	Region region2(16, 16);
	Region region3(16, 16);
	Region region4(16, 16);
	sb.build(region1, 0, 0);
	map.addRegion(region1, 0, 0);
	sb.build(region2, 16, 0);
	map.addRegion(region2, 1, 0);
	sb.build(region3, 32, 0);
	map.addRegion(region3, 2, 0);
	sb.build(region4, 64, 0);
	map.addRegion(region4, 3, 0);

	/*Noise2D<float> test;
	for(float i = 0.f; i < 2.f; i += 0.01f)
	{
		std::cout << ":" << test.getValue(static_cast<float>(i), 0.01f) << " ";
	}

	std::cout << std::endl << std::endl;

	test.setOctave(2);
	for(float i = 0.f; i < 2.f; i += 0.1f)
	{
		std::cout << test.getValue(static_cast<float>(i), 0.01f) << " ";
	}

	std::cout << std::endl << std::endl;

	test.setSeed(8489);
	for(float i = 0.f; i < 2.f; i += 0.1f)
	{
		std::cout << test.getValue(static_cast<float>(i), 0.01f) << " ";
	}*/
	
	/*sb.build(region, 4);
	sb.build(region, 8);
	sb.build(region, 12);*/
	//std::cout << map.toString() << std::endl;


	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
	unsigned char minValue = 0;
	sf::Uint8 maxValue = 255;
	Noise2D<int> perl = Noise2D<int>(1113, 0, maxValue, 0.2f, 10,
			0.5f, 2.f);
	//perl.setNoiseType(NoiseType::Billow);
	sf::Uint8* image = new sf::Uint8[200 * 200 * 4];
	initArray(image, 200, 200);
	perlinToArray(image, perl, 200, 200);
	sf::Texture texture;
	if (!texture.create(200, 200))
		return -1;

	sf::Sprite sprite(texture);
	texture.update(image);
	
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}

/*int main()
{
	const ns::module::Perlin pModule;
	ns::utils::NoiseMap noiseMap;
	ns::utils::NoiseMapBuilderPlane nmBuilder;
	nmBuilder.SetSourceModule(pModule);
	nmBuilder.SetDestNoiseMap(noiseMap);
	nmBuilder.SetDestSize(256, 256);
	nmBuilder.SetBounds(2.0, 6.0, 1.0, 5.0);
	nmBuilder.Build();

	utils::RendererImage renderer;
	utils::Image image;
	renderer.SetSourceNoiseMap(noiseMap);
	renderer.SetDestImage(image);
	renderer.Render();
	utils::WriterBMP writer;
	writer.SetSourceImage(image);
	writer.SetDestFilename("tutorial.bmp");
	writer.WriteDestFile();
}*/
