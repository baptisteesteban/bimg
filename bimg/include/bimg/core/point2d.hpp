#pragma once

namespace bimg
{
  struct point2d
  {
    int x;
    int y;
  };

  inline constexpr point2d operator+(const point2d& p1, const point2d& p2) noexcept
  {
    return point2d{p1.x + p2.x, p1.y + p2.y};
  }

  inline constexpr bool operator==(const point2d& p1, const point2d& p2) noexcept
  {
    return p1.x == p2.x && p1.y == p2.y;
  }

  inline constexpr bool operator!=(const point2d& p1, const point2d& p2) noexcept
  {
    return !(p1 == p2);
  }
} // namespace bimg