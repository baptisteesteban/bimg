#include <bimg/core/neighborhoods/c8.hpp>
#include <bimg/distance_transforms/generalised_geodesic.hpp>

#include <gtest/gtest.h>

TEST(GeneralisedGeodesic, Geodesic)
{
  using namespace bimg;

  const image2d<std::uint8_t> img{
      {3, 9, 1, 6}, //
      {9, 3, 2, 1}, //
      {2, 5, 1, 0}, //
      {1, 4, 9, 3}  //
  };

  const image2d<bool> mask{
      {false, false, false, false}, //
      {false, true, true, false},   //
      {false, true, false, false},  //
      {false, false, false, false}  //
  };

  const image2d<float> ref{
      {0, 4, 1, 4}, //
      {4, 0, 0, 1}, //
      {1, 0, 1, 2}, //
      {2, 1, 4, 3}  //
  };

  const auto res = dt::generalised_geodesic(img, mask, c8, 1);

  ASSERT_EQ(res.width(), ref.width());
  ASSERT_EQ(res.height(), ref.height());

  for (auto p : res.domain())
    ASSERT_EQ(res(p), ref(p));
}