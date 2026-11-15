#pragma once

#include <bimg/core/point2d.hpp>

#include <array>
#include <ranges>

namespace bimg
{
  class c4_t
  {
  public:
    using point_t = point2d;

  public:
    constexpr c4_t() noexcept = default;
    constexpr auto operator()(const point2d& p) const noexcept
    {
      return offsets | std::views::transform([&](const auto& o) { return p + o; });
    }
    constexpr auto before(const point2d& p) const noexcept
    {
      return offsets | std::views::take(2) | std::views::transform([&](const auto& o) { return p + o; });
    }


  private:
    static constexpr std::array<point2d, 4> offsets = {point2d{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
  };

  static constexpr c4_t c4{};
} // namespace bimg