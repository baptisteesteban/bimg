#include <bimg/core/neighborhoods/c4.hpp>
#include <bimg/labeling/rag.hpp>

#include <gtest/gtest.h>

TEST(RAG, RAG_C4)
{
  using namespace bimg;

  const bool ref[] = {
      false, true,  true,  false, true,  //
      true,  false, true,  false, false, //
      true,  true,  false, true,  false, //
      false, false, true,  false, true,  //
      true,  false, false, true,  false, //
  };

  const image2d<std::uint16_t> labels{
      {0, 1, 2, 2}, //
      {0, 0, 2, 3}, //
      {0, 0, 0, 4}  //
  };

  int        n_nodes = -1;
  const auto rag     = labeling::rag(labels, c4, n_nodes);

  ASSERT_EQ(n_nodes, 5);

  for (int n1 = 0; n1 < n_nodes; n1++)
  {
    for (int n2 = 0; n2 < n_nodes; n2++)
      ASSERT_EQ(rag[n1 * n_nodes + n2], ref[n1 * n_nodes + n2]);
  }
}