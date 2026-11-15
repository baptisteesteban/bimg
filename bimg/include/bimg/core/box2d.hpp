#pragma once

#include <bimg/core/point2d.hpp>

namespace bimg
{
  class box2d
  {
  public:
    using point_t = point2d;

  public:
    class iterator;

  public:
    constexpr box2d() noexcept                        = default;
    constexpr box2d(const box2d&) noexcept            = default;
    constexpr box2d(box2d&&) noexcept                 = default;
    constexpr box2d& operator=(const box2d&) noexcept = default;
    constexpr box2d& operator=(box2d&&) noexcept      = default;

    constexpr box2d(int width, int height) noexcept;

    constexpr bool has(const point_t&) const noexcept;
    constexpr int  width() const noexcept;
    constexpr int  height() const noexcept;
    constexpr int  size() const noexcept;

    constexpr iterator begin() const noexcept;
    constexpr iterator end() const noexcept;

  private:
    int m_width;
    int m_height;
  };

  class box2d::iterator
  {
  public:
    using value_t = point2d;

  public:
    constexpr iterator(int stride, int cur = 0) noexcept;

    constexpr iterator& operator++() noexcept;
    constexpr iterator  operator++(int) noexcept;
    constexpr point2d   operator*() const noexcept;

    constexpr bool operator==(const iterator&) const noexcept;
    constexpr bool operator!=(const iterator&) const noexcept;

  private:
    int m_stride;
    int m_cur;
  };

  /*
   * Implementation
   */

  constexpr box2d::iterator::iterator(int stride, int cur) noexcept
    : m_stride(stride)
    , m_cur(cur)
  {
  }

  constexpr box2d::iterator& box2d::iterator::operator++() noexcept
  {
    ++m_cur;
    return *this;
  }

  constexpr box2d::iterator box2d::iterator::operator++(int) noexcept
  {
    auto copy = *this;
    ++(*this);
    return copy;
  }

  constexpr point2d box2d::iterator::operator*() const noexcept
  {
    return point2d{m_cur % m_stride, m_cur / m_stride};
  }

  inline constexpr bool box2d::iterator::operator==(const iterator& other) const noexcept
  {
    return m_stride == other.m_stride && m_cur == other.m_cur;
  }

  inline constexpr bool box2d::iterator::operator!=(const iterator& other) const noexcept
  {
    return !(*this == other);
  }

  constexpr box2d::box2d(int width, int height) noexcept
    : m_width(width)
    , m_height(height)
  {
  }

  inline constexpr bool box2d::has(const point2d& p) const noexcept
  {
    return p.x >= 0 && p.x < m_width && p.y >= 0 && p.y < m_height;
  }


  inline constexpr int box2d::width() const noexcept
  {
    return m_width;
  }

  inline constexpr int box2d::height() const noexcept
  {
    return m_height;
  }

  inline constexpr int box2d::size() const noexcept
  {
    return m_width * m_height;
  }

  constexpr box2d::iterator box2d::begin() const noexcept
  {
    return iterator(m_width);
  }

  constexpr box2d::iterator box2d::end() const noexcept
  {
    return iterator(m_width, size());
  }
} // namespace bimg