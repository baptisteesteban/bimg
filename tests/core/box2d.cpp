#include <bimg/core/box2d.hpp>

#include <gtest/gtest.h>

#include <iostream>

TEST(Box2d, Box2d)
{
  using namespace bimg;

  const box2d b1{4, 9};
  ASSERT_EQ(b1.width(), 4);
  ASSERT_EQ(b1.height(), 9);
  ASSERT_EQ(b1.size(), 36);

  ASSERT_TRUE(b1.has(point2d{0, 0}));
  ASSERT_TRUE(b1.has(point2d{3, 6}));
  ASSERT_FALSE(b1.has(point2d{4, 3}));
  ASSERT_FALSE(b1.has(point2d{3, 9}));
  ASSERT_FALSE(b1.has(point2d{4, 9}));
}

TEST(Box2d, Range)
{
  using namespace bimg;

  static constexpr point2d refs[] = {{0, 0}, {1, 0}, {2, 0}, {0, 1}, {1, 1}, {2, 1}};

  const box2d domain{3, 2};
  int         i = 0;
  for (const auto& p : domain)
  {
    std::cout << p.x << " " << p.y << "\n";
    ASSERT_EQ(p, refs[i++]);
  }
}