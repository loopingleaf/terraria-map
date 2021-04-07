#include <iostream>

#include "Map.h"
#include "SurfaceBuilder.h"
#include "noise/noise.h"
#include "noiseutils.h"

namespace ns = noise;

int main()
{
	std::shared_ptr<ns::module::Perlin> perlin = std::make_shared<ns::module::Perlin>();
	perlin->SetSeed(1456);
	auto line = std::make_shared<ns::model::Line>();
	SurfaceBuilder sb(perlin, 0.05);
	
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

	Region region1(4, 4);
	Region region2(4, 4);
	Region region3(4, 4);
	Region region4(4, 4);
	sb.build(region1, 0);
	map.addRegion(region1, 0, 0);
	sb.build(region2, 4);
	map.addRegion(region2, 1, 0);
	sb.build(region3, 8);
	map.addRegion(region3, 2, 0);
	sb.build(region4, 12);
	map.addRegion(region4, 3, 0);
	
	/*sb.build(region, 4);
	sb.build(region, 8);
	sb.build(region, 12);*/
	std::cout << map.toString() << std::endl;
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
