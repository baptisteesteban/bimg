#include <bimg/io/imread.hpp>
#include <bimg/io/imwrite.hpp>

#include <cstring>

#include <gtest/gtest.h>

TEST(IO, image2d_uint8_t)
{
  using namespace bimg;

  std::uint8_t data[] = {4, 2, 9, 6, 8, 1};

  image2d<std::uint8_t> img(3, 2);
  std::memcpy(img.buffer(), data, 6);
  io::imwrite("tmp.png", img);

  image2d<std::uint8_t> img2;
  io::imread("tmp.png", img2);

  ASSERT_EQ(img.width(), img2.width());
  ASSERT_EQ(img.height(), img2.height());

  for (int y = 0; y < img.height(); y++)
  {
    for (int x = 0; x < img.width(); x++)
      ASSERT_EQ(img(x, y), img2(x, y));
  }
}