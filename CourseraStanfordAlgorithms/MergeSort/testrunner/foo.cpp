#include <cstdlib>

#include <algorithm>
#include <iostream>

#include <gtest/gtest.h>

#include <library/foo.h>

class MergeSortFuzzyTest
    : public ::testing::TestWithParam<int> {};

TEST_P(MergeSortFuzzyTest, MergeSortTest) {
  auto length = (std::rand() % 400) + 1;
  std::vector<size_t> table;
  table.reserve(length);

  for (;0 != length; --length) {
    table.push_back(std::rand() % 100);
  }

  auto second_table = table;

  std::sort(std::begin(table), std::end(table));
  merge_sort(std::begin(second_table), std::end(second_table));

  std::cout << "Std sort" << std::endl;
  for(auto elem : table) {
    std::cout << elem << " ";
  }
  std::cout << std::endl << std::endl;
  std::cout << "Merge_sort" << std::endl;
  for (auto elem : second_table) {
    std::cout << elem << " ";
  }

  ASSERT_TRUE(table == second_table);
}

INSTANTIATE_TEST_CASE_P(Suite, MergeSortFuzzyTest, ::testing::Range(1, 1000));
