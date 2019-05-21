#include <cstdlib>

#include <algorithm>
#include <iostream>

#include <gtest/gtest.h>

#include <library/foo.h>


namespace {
  template <typename Iter>
  ssize_t count_inversions_bruteforce(Iter first, Iter last) {
    ssize_t answer {};

    if(2 > std::distance(first, last)) {
      return answer;
    }

    for (; first != last; first = std::next(first)) {
      for (Iter i = std::next(first); i != last; i = std::next(i)) {
        if (*first >= *i) {
          ++answer;
        }
      }
    }

    return answer;
  }
}

class CountConverntionFuzzyTest
    : public ::testing::TestWithParam<int> {};

TEST_P(CountConverntionFuzzyTest, MergeSortTest) {
  auto length = (std::rand() % 40) + 1;
  std::vector<size_t> table;
  table.reserve(length);

  for (;0 != length; --length) {
    table.push_back(std::rand() % 100);
  }

  std::cout << std::endl << "Table: ";
  for (auto elem : table) {
    std::cout << elem << " ";
  }
  std::cout << std::endl;

  const auto alg_result =
      count_inversions(std::begin(table), std::end(table));
  const auto brute_result =
      count_inversions_bruteforce(std::begin(table), std::end(table));

  ASSERT_EQ(alg_result, brute_result);
}

INSTANTIATE_TEST_CASE_P(Suite, CountConverntionFuzzyTest, ::testing::Range(1, 1000));
