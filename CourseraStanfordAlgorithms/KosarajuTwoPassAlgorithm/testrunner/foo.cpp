#include <gtest/gtest.h>
#include <library/foo.h>

TEST(FooForumCases, FirstCase) {
  Graph graph{{3}, {7}, {5}, {6}, {1}, {8}, {0}, {4, 5}, {6, 2}};

  const auto scc_sizes = FindSCCs(graph);

  const std::vector<std::size_t> expected_scc_sizes{3, 3, 3, 0, 0};

  ASSERT_EQ(scc_sizes, expected_scc_sizes);
}

TEST(FooForumCases, SecondTest) {
  Graph graph{{1}, {5, 2, 3}, {0, 3}, {4}, {3}, {4, 6}, {5, 7}, {4, 6}};

  const auto scc_sizes = FindSCCs(graph);

  const std::vector<std::size_t> expected_scc_sizes{3, 3, 2, 0, 0};

  ASSERT_EQ(scc_sizes, expected_scc_sizes);
}

