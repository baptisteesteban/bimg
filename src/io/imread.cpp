#include <bimg/io/imread.hpp>

#include <cstdint>
#include <cstring>

#include "stb_image.h"

namespace bimg::io
{
  template <>
  void imread<std::uint8_t>(const char* filename, image2d<std::uint8_t>& img)
  {
    int  width, height, n;
    auto data = stbi_load(filename, &width, &height, &n, 1);
    assert(n == 1);
    img.resize(width, height);
    std::memcpy(img.buffer(), data, width * height);
    stbi_image_free(data);
  }
} // namespace bimg::io