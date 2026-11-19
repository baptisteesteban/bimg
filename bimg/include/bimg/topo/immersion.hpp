#pragma once

#include <bimg/core/image2d.hpp>
#include <bimg/core/neighborhoods/c4.hpp>

#include <algorithm>
#include <limits>
#include <utility>

namespace bimg::topo
{
  template <typename T>
  std::pair<image2d<T>, image2d<T>> immersion(const image2d<T>& img);

  /*
   * Implementation
   */

  template <typename T>
  std::pair<image2d<T>, image2d<T>> immersion(const image2d<T>& img)
  {
    const int kwidth  = 2 * img.width() - 1;
    const int kheight = 2 * img.height() - 1;

    image2d<T> m(kwidth, kheight);
    image2d<T> M(kwidth, kheight);

    // 2-faces
    for (auto p : img.domain())
    {
      const auto kp = point2d(p.x * 2, p.y * 2);
      m(kp)         = img(p);
      M(kp)         = img(p);
    }

    // 1-faces vectical
    for (int y = 0; y < m.height(); y += 2)
    {
      for (int x = 1; x < m.width(); x += 2)
      {
        const auto [min_v, max_v] = std::minmax(m(x - 1, y), m(x + 1, y));
        m(x, y)                   = min_v;
        M(x, y)                   = max_v;
      }
    }

    // 1-faces horizontal
    for (int y = 1; y < m.height(); y += 2)
    {
      for (int x = 0; x < m.width(); x += 2)
      {
        const auto [min_v, max_v] = std::minmax(m(x, y - 1), m(x, y + 1));
        m(x, y)                   = min_v;
        M(x, y)                   = max_v;
      }
    }

    // 0-faces
    for (int y = 1; y < m.height(); y += 2)
    {
      for (int x = 1; x < m.width(); x += 2)
      {
        const point2d p{x, y};
        T             min_v = std::numeric_limits<T>::max();
        T             max_v = std::numeric_limits<T>::min();
        for (auto q : c4(p))
        {
          min_v = std::min(min_v, m(q));
          max_v = std::max(max_v, M(q));
        }
        m(p) = min_v;
        M(p) = max_v;
      }
    }

    return {m, M};
  }
} // namespace bimg::topo