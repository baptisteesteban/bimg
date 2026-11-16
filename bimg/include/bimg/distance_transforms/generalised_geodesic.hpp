#pragma once

#include <bimg/core/image2d.hpp>
#include <bimg/core/neighborhoods/c4.hpp>

#include <limits>
#include <queue>
#include <vector>

namespace bimg::dt
{
  template <typename T>
  image2d<float> generalised_geodesic(const image2d<T>& img, const image2d<bool>& mask)
  {
    using queue_value_t = std::pair<float, point2d>;
    image2d<float> res(img.width(), img.height());
    const auto     cmp = [](const queue_value_t& u, const queue_value_t& v) { return u.first > v.first; };
    std::priority_queue<queue_value_t, std::vector<queue_value_t>, decltype(cmp)> q(cmp);
    image2d<bool>                                                                 visited(img.width(), img.height());

    // Initialization
    for (auto p : img.domain())
    {
      if (mask(p))
      {
        res(p) = 0;
        q.push({0, p});
      }
      else
        res(p) = std::numeric_limits<float>::max();
      visited(p) = false;
    }

    // Propagation
    while (!q.empty())
    {
      const auto [v, p] = q.top();
      q.pop();

      if (visited(p))
        continue;

      visited(p) = true;

      for (auto n : c4(p))
      {
        if (!res.domain().has(n) || visited(n))
          continue;
        const float d_new = res(p) + std::abs(static_cast<float>(img(p)) - static_cast<float>(img(n)));
        if (d_new < res(n))
        {
          res(n) = d_new;
          q.push({d_new, n}); // Update the priority by lazy deletion
        }
      }
    }

    return res;
  }
} // namespace bimg::dt