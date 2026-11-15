#include <bimg/core/neighborhoods/c4.hpp>
#include <bimg/core/neighborhoods/c8.hpp>
#include <bimg/labeling/connected_components.hpp>

#include <gtest/gtest.h>

TEST(ConnectedComponents, UnionFind_C4)
{
  using namespace bimg;

  const image2d<std::uint8_t> img{
      {1, 4, 3, 3}, //
      {1, 1, 3, 4}, //
      {1, 1, 1, 3}  //
  };

  const image2d<std::uint16_t> ref{
      {0, 1, 2, 2}, //
      {0, 0, 2, 3}, //
      {0, 0, 0, 4}  //
  };

  const auto res = labelling::connected_components(img, c4);

  ASSERT_EQ(res.width(), ref.width());
  ASSERT_EQ(res.height(), ref.height());

  for (int y = 0; y < res.height(); y++)
  {
    for (int x = 0; x < res.width(); x++)
      ASSERT_EQ(res(x, y), ref(x, y));
  }
}

TEST(ConnectedComponents, UnionFind_C8)
{
  using namespace bimg;

  const image2d<std::uint8_t> img{
      {1, 4, 3, 3}, //
      {1, 1, 3, 4}, //
      {1, 1, 1, 3}  //
  };

  const image2d<std::uint16_t> ref{
      {0, 1, 2, 2}, //
      {0, 0, 2, 3}, //
      {0, 0, 0, 2}  //
  };

  const auto res = labelling::connected_components(img, c8);

  ASSERT_EQ(res.width(), ref.width());
  ASSERT_EQ(res.height(), ref.height());

  for (int y = 0; y < res.height(); y++)
  {
    for (int x = 0; x < res.width(); x++)
      ASSERT_EQ(res(x, y), ref(x, y));
  }
}