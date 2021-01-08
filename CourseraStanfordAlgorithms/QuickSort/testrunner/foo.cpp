#include <gtest/gtest.h>
#include <library/foo.h>

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>

class QuickSortFuzzyTest : public ::testing::TestWithParam<int> {};

TEST_P(QuickSortFuzzyTest, QuickSortTest_FirstPivot) {
  std::vector<size_t> table;
  using Iter = decltype(table)::iterator;

  constexpr size_t kSize = 50;
  table.reserve(kSize);
  for (size_t i = 0; i < kSize; ++i) {
    table.push_back(std::rand() % 100);
  }
  auto second_table(table);

  std::sort(table.begin(), table.end());
  QuickSort<Iter, Pivot::kFirst>(second_table.begin(), second_table.end());

  ASSERT_TRUE(table == second_table);
}

TEST_P(QuickSortFuzzyTest, QuickSortTest_kLastPivot) {
  std::vector<size_t> table;
  using Iter = decltype(table)::iterator;

  constexpr size_t kSize = 50;
  table.reserve(kSize);
  for (size_t i = 0; i < kSize; ++i) {
    table.push_back(std::rand() % 100);
  }
  auto second_table(table);

  std::sort(table.begin(), table.end());
  QuickSort<Iter, Pivot::kLast>(second_table.begin(), second_table.end());

  ASSERT_TRUE(table == second_table);
}

TEST_P(QuickSortFuzzyTest, QuickSortTest_kMedian) {
  std::vector<size_t> table;
  using Iter = decltype(table)::iterator;

  constexpr size_t kSize = 50;
  table.reserve(kSize);
  for (size_t i = 0; i < kSize; ++i) {
    table.push_back(std::rand() % 100);
  }
  auto second_table(table);

  std::sort(table.begin(), table.end());
  QuickSort<Iter, Pivot::kMedian>(second_table.begin(), second_table.end());

  ASSERT_TRUE(table == second_table);
}

INSTANTIATE_TEST_SUITE_P(Suite, QuickSortFuzzyTest, ::testing::Range(1, 1000));
