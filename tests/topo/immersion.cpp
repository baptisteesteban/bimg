#include <bimg/core/image2d.hpp>
#include <bimg/topo/immersion.hpp>

#include <gtest/gtest.h>

TEST(Immersion, Image2d)
{
  using namespace bimg;

  const image2d<std::uint8_t> img{
      {1, 4, 3}, //
      {9, 2, 6}, //
      {9, 1, 4}  //
  };

  const image2d<std::uint8_t> ref_m{
      {1, 1, 4, 3, 3}, //
      {1, 1, 2, 2, 3}, //
      {9, 2, 2, 2, 6}, //
      {9, 1, 1, 1, 4}, //
      {9, 1, 1, 1, 4}  //
  };

  const image2d<std::uint8_t> ref_M{
      {1, 4, 4, 4, 3}, //
      {9, 9, 4, 6, 6}, //
      {9, 9, 2, 6, 6}, //
      {9, 9, 2, 6, 6}, //
      {9, 9, 1, 4, 4}  //
  };

  const auto [m, M] = topo::immersion(img);

  ASSERT_EQ(m.width(), ref_m.width());
  ASSERT_EQ(m.height(), ref_m.height());
  ASSERT_EQ(M.width(), ref_M.width());
  ASSERT_EQ(M.height(), ref_M.height());
  for (auto p : m.domain())
  {
    ASSERT_EQ(m(p), ref_m(p));
    ASSERT_EQ(M(p), ref_M(p));
  }
}