#pragma once

#include <bimg/core/image2d.hpp>

#include <algorithm>
#include <memory>

namespace bimg::labeling
{
  template <typename N>
  std::unique_ptr<bool[]> rag(const image2d<std::uint16_t>& labels, N nbh, int& n_nodes)
  {
    const auto domain = labels.domain();
    n_nodes           = *std::max_element(labels.buffer(), labels.buffer() + domain.size()) + 1;

    auto rag = std::make_unique<bool[]>(n_nodes * n_nodes);

    for (const auto p : domain)
    {
      for (const auto n : nbh.before(p))
      {
        const auto n_p = labels(p);
        if (domain.has(n) && n_p != labels(n))
        {
          const auto n_n           = labels(n);
          rag[n_n * n_nodes + n_p] = true;
          rag[n_p * n_nodes + n_n] = true;
        }
      }
    }

    return rag;
  }
} // namespace bimg::labeling