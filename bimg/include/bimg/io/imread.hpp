#pragma once

#include <bimg/core/image2d.hpp>

namespace bimg::io
{
  template <typename T>
  void imread(const char* filename, image2d<T>& img);
}