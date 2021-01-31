#include <gtest/gtest.h>
#include <library/foo.h>

TEST(FindShortestDistanceTestSuite, TrivialCase) {
  Graph graph{{0U, {{1U, 1U}}}, {1U, {{0U, 1U}}}};
  const auto shortest_path_0to1 = FindShortestDistance(graph, 0U, 1U);
  const auto shortest_path_1to0 = FindShortestDistance(graph, 1U, 0U);
  const auto shortest_path_0to2 = FindShortestDistance(graph, 0U, 2U);

  ASSERT_EQ(shortest_path_0to1, 1U);
  ASSERT_EQ(shortest_path_1to0, 1U);
  ASSERT_EQ(shortest_path_0to2, kUnconnectedDistance);
}

TEST(FindShortestDistanceTestSuite, SmallCase) {
  Graph graph{{0U, {{1U, 999U}, {2U, 1U}}},
              {1U, {{0U, 999U}, {2U, 6U}, {3U, 3U}}},
              {2U, {{0U, 1U}, {1U, 6U}, {3U, 2U}}},
              {3U, {{1U, 3U}, {2U, 2U}}}};
  const auto shortest_path_0to2 = FindShortestDistance(graph, 0U, 2U);
  const auto shortest_path_0to3 = FindShortestDistance(graph, 0U, 3U);
  const auto shortest_path_0to1 = FindShortestDistance(graph, 0U, 1U);
  const auto shortest_path_1to2 = FindShortestDistance(graph, 1U, 2U);

  ASSERT_EQ(shortest_path_0to2, 1U);
  ASSERT_EQ(shortest_path_0to3, 3U);
  ASSERT_EQ(shortest_path_0to1, 6U);
  ASSERT_EQ(shortest_path_1to2, 5U);
}

