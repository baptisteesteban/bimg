#include <bimg/core/image2d.hpp>

#include <gtest/gtest.h>

#include <utility>

#define TEST_IMG_EQ(img1, img2)                                                                                        \
  ASSERT_EQ(img1.width(), img2.width());                                                                               \
  ASSERT_EQ(img1.height(), img2.height());                                                                             \
  for (int y = 0; y < img2.height(); y++)                                                                              \
  {                                                                                                                    \
    for (int x = 0; x < img2.width(); x++)                                                                             \
      ASSERT_EQ(img2(x, y), img1(x, y));                                                                               \
  }

TEST(Image2d, Image2d)
{
  using namespace bimg;

  std::uint8_t data[] = {3, 9, 1, 5, 3, 9};

  image2d<std::uint8_t> img(3, 2);
  ASSERT_EQ(img.width(), 3);
  ASSERT_EQ(img.height(), 2);

  for (int y = 0; y < img.height(); y++)
  {
    for (int x = 0; x < img.width(); x++)
      img(x, y) = data[y * img.width() + x];
  }

  image2d<std::uint8_t> img2 = img;
  TEST_IMG_EQ(img, img2);

  image2d<std::uint8_t> img3(img);
  TEST_IMG_EQ(img, img3);

  const auto img4 = std::move(img2);
  TEST_IMG_EQ(img, img4);
  ASSERT_EQ(img2.width(), 0);
  ASSERT_EQ(img2.height(), 0);
  ASSERT_EQ(img2.buffer(), nullptr);

  const image2d<std::uint8_t> img5(std::move(img3));
  TEST_IMG_EQ(img, img5);
  ASSERT_EQ(img3.width(), 0);
  ASSERT_EQ(img3.height(), 0);
  ASSERT_EQ(img3.buffer(), nullptr);

  const auto domain = img.domain();
  ASSERT_EQ(domain.width(), img.width());
  ASSERT_EQ(domain.height(), img.height());
}

TEST(Image2d, Resize)
{
  using namespace bimg;

  std::uint8_t data[] = {3, 9, 1, 5, 3, 9};

  image2d<std::uint8_t> img;
  img.resize(2, 3);
  for (int y = 0; y < img.height(); y++)
  {
    for (int x = 0; x < img.width(); x++)
      img(x, y) = data[y * img.width() + x];
  }
  for (int y = 0; y < img.height(); y++)
  {
    for (int x = 0; x < img.width(); x++)
      ASSERT_EQ(img(x, y), data[y * img.width() + x]);
  }
}

TEST(Image2d, Point2d)
{
  using namespace bimg;

  std::uint8_t data[] = {3, 9, 1, 5, 3, 9};

  image2d<std::uint8_t> img(3, 2);
  for (int y = 0; y < img.height(); y++)
  {
    for (int x = 0; x < img.width(); x++)
      img(x, y) = data[y * img.width() + x];
  }

  for (int y = 0; y < img.height(); y++)
  {
    for (int x = 0; x < img.width(); x++)
    {
      const point2d p{x, y};
      ASSERT_EQ(img(p), data[y * img.width() + x]);
      ASSERT_EQ(img(p), img(x, y));
    }
  }
}

TEST(Image2d, InitializerList)
{
  using namespace bimg;

  std::uint8_t          data[] = {3, 9, 1, 5, 3, 9};
  image2d<std::uint8_t> img{{3, 9, 1}, {5, 3, 9}};
  ASSERT_EQ(img.width(), 3);
  ASSERT_EQ(img.height(), 2);

  for (int y = 0; y < img.height(); y++)
  {
    for (int x = 0; x < img.width(); x++)
      ASSERT_EQ(img(x, y), data[y * img.width() + x]);
  }
}