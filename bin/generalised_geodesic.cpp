#include <bimg/distance_transforms/generalised_geodesic.hpp>
#include <bimg/io/imread.hpp>
#include <bimg/io/imwrite.hpp>

#include <print>

int main(int argc, char* argv[])
{
  using namespace bimg;

  if (argc < 4)
  {
    std::print("Usage: {} input_image[grayscale] input_mask[grayscale] output_image[grayscale]\n", argv[0]);
    return 1;
  }

  const char* input_filename        = argv[1];
  const char* input_mask_filename   = argv[2];
  const char* output_image_filename = argv[3];

  image2d<std::uint8_t> img;
  image2d<std::uint8_t> mask_int;
  io::imread(input_filename, img);
  io::imread(input_mask_filename, mask_int);

  image2d<bool> mask(mask_int.width(), mask_int.height());
  for (auto p : mask_int.domain())
    mask(p) = mask_int(p) > 0 ? true : false;

  const auto dt_float = dt::generalised_geodesic(img, mask);

  float max_d = 0;
  for (auto p : dt_float.domain())
  {
    if (dt_float(p) > max_d)
      max_d = dt_float(p);
  }

  image2d<std::uint8_t> dt(dt_float.width(), dt_float.height());
  for (auto p : dt_float.domain())
    dt(p) = static_cast<std::uint8_t>((dt_float(p) / max_d) * 255);

  io::imwrite(output_image_filename, dt);

  return 0;
}