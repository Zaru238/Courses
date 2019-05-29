#include <cstdlib>

#include <algorithm>
#include <iostream>
#include <vector>

#include <gtest/gtest.h>

#include <library/foo.h>

class QuickSortFuzzyTest
    : public ::testing::TestWithParam<int> {};

TEST_P(QuickSortFuzzyTest, QuickSortTest) {
  std::vector<size_t> table;

  constexpr size_t kSize = 50;
  table.reserve(kSize);
  for(size_t i = 0; i < kSize; ++i) {
    table.push_back(std::rand() % 100);
  }
  auto second_table (table);

  std::sort(table.begin(), table.end());
  QuickSort(second_table.begin(), second_table.end());

  ASSERT_TRUE(table == second_table);
}

INSTANTIATE_TEST_CASE_P(Suite, QuickSortFuzzyTest, ::testing::Range(1, 1000));
