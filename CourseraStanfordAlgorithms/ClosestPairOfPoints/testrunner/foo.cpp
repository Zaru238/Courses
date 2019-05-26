#include <cstdlib>

#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>

#include <gtest/gtest.h>

#include <library/foo.h>


class FindClosestPointsFuzzyTest
    : public ::testing::TestWithParam<int> {};

TEST_P(FindClosestPointsFuzzyTest, MergeSortTest) {
  std::set<Point> unique_points;
  while (unique_points.size() != 100) {
    unique_points.insert(
        std::make_pair(std::rand() % 1000, std::rand() % 1000));
  }

  std::vector<Point> points(std::begin(unique_points), std::end(unique_points));
  std::random_shuffle(points.begin(), points.end());

  const auto bruteforce_result = FindClosestPairBruteforce(points);
  const auto divide_conquer_result = FindClosestPairDivideAndConquer(points);

  std::cout << "Result " << bruteforce_result << " " << divide_conquer_result
            << std::endl;
  ASSERT_EQ(bruteforce_result, divide_conquer_result);
}

INSTANTIATE_TEST_CASE_P(Suite, FindClosestPointsFuzzyTest, ::testing::Range(1, 1000));
