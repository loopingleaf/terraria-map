#include <iostream>

#include "SurfaceBuilder.h"
#include "noise/noise.h"
#include "noiseutils.h"

namespace ns = noise;

int main()
{
	ns::module::Perlin perlin;
	perlin.SetSeed(1564);
	auto line = std::make_shared<ns::model::Line>();
	line->SetModule(perlin);
	line->SetStartPoint(0., 0., 0.);
	line->SetEndPoint(1., 0., 0.);
	SurfaceBuilder sb(line, 0.1);
	Region region(25, 25);
	sb.build(region, 0.);
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
