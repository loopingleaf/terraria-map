#include <iostream>
#include "noise/noise.h"
#include "noiseutils.h"

namespace ns = noise;

int main()
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
}
