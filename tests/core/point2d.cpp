#include <bimg/core/point2d.hpp>

#include <gtest/gtest.h>

TEST(Point2d, Point2d)
{
  using namespace bimg;

  const point2d p{9, 4};
  ASSERT_EQ(p.x, 9);
  ASSERT_EQ(p.y, 4);
}