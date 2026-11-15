#pragma once

#include <bimg/core/box2d.hpp>

#include <algorithm>
#include <cassert>
#include <format>
#include <initializer_list>
#include <memory>
#include <stdexcept>
#include <utility>

namespace bimg
{
  template <typename T>
  class image2d
  {
  public:
    using domain_t = box2d;
    using point_t  = domain_t::point_t;

  public:
    image2d() noexcept;
    image2d(int width, int height);
    image2d(std::initializer_list<std::initializer_list<T>> ini);

    image2d(const image2d&) noexcept;
    image2d(image2d&&) noexcept;
    image2d& operator=(const image2d&) noexcept;
    image2d& operator=(image2d&&) noexcept;

    T&       operator()(int x, int y) noexcept;
    const T& operator()(int x, int y) const noexcept;

    T&       operator()(const point2d& p) noexcept;
    const T& operator()(const point2d& p) const noexcept;

    T*       buffer() noexcept;
    const T* buffer() const noexcept;

    int   width() const noexcept;
    int   height() const noexcept;
    box2d domain() const noexcept;

    void resize(int width, int height);

  private:
    int                  m_width;
    int                  m_height;
    std::shared_ptr<T[]> m_data;
  };

  /*
   * Implementation
   */

  template <typename T>
  image2d<T>::image2d() noexcept
    : m_width(0)
    , m_height(0)
    , m_data(nullptr)
  {
  }

  template <typename T>
  image2d<T>::image2d(int width, int height)
    : m_width(width)
    , m_height(height)
  {
    assert(width >= 0 && height >= 0);
    m_data = std::make_unique<T[]>(width * height);
  }

  template <typename T>
  image2d<T>::image2d(std::initializer_list<std::initializer_list<T>> ini)
  {
    m_height = ini.size();
    m_width  = m_height > 0 ? ini.begin()->size() : 0;
    m_data   = std::make_shared<T[]>(m_width * m_height);
    if (m_width > 0)
    {
      T* buffer = m_data.get();
      for (auto it = ini.begin(); it != ini.end(); ++it)
      {
        if (it->size() != m_width)
          throw std::invalid_argument(std::format("Invalid width size (Got {}, expect {})", it->size(), m_width));
        std::copy(it->begin(), it->end(), buffer);
        buffer += m_width;
      }
    }
  }

  template <typename T>
  image2d<T>::image2d(const image2d& other) noexcept
    : m_width(other.m_width)
    , m_height(other.m_height)
    , m_data(other.m_data)
  {
  }

  template <typename T>
  image2d<T>::image2d(image2d&& other) noexcept
    : m_width(std::exchange(other.m_width, 0))
    , m_height(std::exchange(other.m_height, 0))
    , m_data(std::exchange(other.m_data, nullptr))
  {
  }

  template <typename T>
  image2d<T>& image2d<T>::operator=(const image2d& other) noexcept
  {
    this->m_width  = other.m_width;
    this->m_height = other.m_height;
    this->m_data   = other.m_data;
    return *this;
  }

  template <typename T>
  image2d<T>& image2d<T>::operator=(image2d<T>&& other) noexcept
  {
    this->m_width  = std::exchange(other.m_width, 0);
    this->m_height = std::exchange(other.m_height, 0);
    this->m_data   = std::exchange(other.m_data, nullptr);
    return *this;
  }

  template <typename T>
  inline T& image2d<T>::operator()(int x, int y) noexcept
  {
    assert(x >= 0 && y >= 0 && x < m_width && y < m_height);
    return m_data[y * m_width + x];
  }

  template <typename T>
  inline const T& image2d<T>::operator()(int x, int y) const noexcept
  {
    assert(x >= 0 && y >= 0 && x < m_width && y < m_height);
    return m_data[y * m_width + x];
  }

  template <typename T>
  inline T& image2d<T>::operator()(const point2d& p) noexcept
  {
    return this->operator()(p.x, p.y);
  }

  template <typename T>
  inline const T& image2d<T>::operator()(const point2d& p) const noexcept
  {
    return this->operator()(p.x, p.y);
  }

  template <typename T>
  inline T* image2d<T>::buffer() noexcept
  {
    return m_data.get(); // VERY BAD !!!
  }

  template <typename T>
  inline const T* image2d<T>::buffer() const noexcept
  {
    return m_data.get(); // VERY BAD !!!
  }

  template <typename T>
  inline int image2d<T>::width() const noexcept
  {
    return m_width;
  }

  template <typename T>
  inline int image2d<T>::height() const noexcept
  {
    return m_height;
  }

  template <typename T>
  inline box2d image2d<T>::domain() const noexcept
  {
    return box2d{m_width, m_height};
  }

  template <typename T>
  void image2d<T>::resize(int width, int height)
  {
    assert(width >= 0 && height >= 0);
    m_width  = width;
    m_height = height;
    m_data   = std::make_shared<T[]>(width * height);
  }
} // namespace bimg