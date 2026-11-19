#include <bimg/io/imread.hpp>
#include <bimg/io/imwrite.hpp>
#include <bimg/topo/immersion.hpp>

#include <format>
#include <print>

int main(int argc, char* argv[])
{
  if (argc < 3)
  {
    std::print("Usage: {} input_image[grayscale] output_distance_transform[grayscale]", argv[0]);
    return 1;
  }

  using namespace bimg;

  const char* input_filename  = argv[1];
  const char* output_filename = argv[2];

  image2d<std::uint8_t> img;
  io::imread(input_filename, img);

  const auto [m, M] = topo::immersion(img);

  io::imwrite(std::format("m_{}", output_filename).c_str(), m);
  io::imwrite(std::format("M_{}", output_filename).c_str(), M);

  return 0;
}