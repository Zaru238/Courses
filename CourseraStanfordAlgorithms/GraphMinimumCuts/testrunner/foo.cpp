#include <gtest/gtest.h>

#include <library/foo.h>

TEST(Foo, DefaultCase) {
  graph::AdjacencyLists data {{1, {2,3,4}},
                              {2, {1,3,4}},
                              {3, {1,2,4}},
                              {4, {1,2,3}}};

  const auto answer = graph::MinCut(data);
  ASSERT_EQ(answer, 3);
}
