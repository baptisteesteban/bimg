#include <bimg/io/imwrite.hpp>

#include <cstdint>

#include "stb_image_write.h"

namespace bimg::io
{
  template <>
  void imwrite<std::uint8_t>(const char* filename, const image2d<std::uint8_t>& img)
  {
    // TODO: add check filename ends with .png
    stbi_write_png(filename, img.width(), img.height(), 1, img.buffer(), img.width());
  }
} // namespace bimg::io