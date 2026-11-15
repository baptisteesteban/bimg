#pragma once

#include <bimg/core/image2d.hpp>

namespace bimg::io
{
  template <typename T>
  void imwrite(const char* filename, const image2d<T>& img);
}