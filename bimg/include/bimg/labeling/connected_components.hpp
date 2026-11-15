#pragma once

#include <bimg/core/image2d.hpp>

#include <cstdint>

namespace bimg::labelling
{
  template <typename T, typename N>
  image2d<std::uint16_t> connected_components(const image2d<T>& img, N nbh, std::uint16_t start_label = 0);

  /*
   * IMPLEMENTATION
   */

  template <typename T, typename N>
  image2d<std::uint16_t> connected_components(const image2d<T>& img, N nbh, std::uint16_t start_label)
  {
    static constexpr std::uint16_t UNLABELED = -1;
    static constexpr point2d       UNVISITED = point2d{-1, -1};

    image2d<std::uint16_t> res(img.width(), img.height());
    image2d<point2d>       par(img.width(), img.height());

    for (int y = 0; y < img.height(); y++)
    {
      for (int x = 0; x < img.width(); x++)
      {
        res(x, y) = UNLABELED;
        par(x, y) = UNVISITED;
      }
    }

    // Union-find
    const auto domain = img.domain();
    for (const auto p : domain)
    {
      // MakeSet
      par(p) = p;
      for (const auto& n : nbh.before(p))
      {
        if (domain.has(n) && img(p) == img(n))
        {
          // Union
          par(p) = par(n);
        }
      }
    }

    // Labelize;
    for (const auto p : domain)
    {
      const auto q = par(p);
      if (res(q) == UNLABELED)
        res(q) = start_label++;
      res(p) = res(q);
    }

    return res;
  }
} // namespace bimg::labelling