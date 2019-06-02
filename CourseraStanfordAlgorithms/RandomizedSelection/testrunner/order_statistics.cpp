#include <cstdlib>

#include <algorithm>
#include <iterator>
#include <vector>

#include <gtest/gtest.h>

#include <library/order_statistics_deterministic.h>
#include <library/order_statistics_random.h>

class OrderStatisticsFuzzyTest : public ::testing::TestWithParam<int> {};

TEST_P(OrderStatisticsFuzzyTest, OrderStaticsticsTest) {
  const size_t kDataSize = std::rand() % 1000 + 1;
  std::vector<size_t> data(kDataSize);

  for (auto& elem : data) {
    elem = rand() % 1000;
  }

  const size_t searched_element = std::rand() % kDataSize;

  const auto order_stat_random_result =
      OrderStatisticsRandom(data.begin(), data.end(), searched_element);
  const auto order_stat_det_result =
      OrderStatisticsDeterministic(data.begin(), data.end(), searched_element);

  std::sort(data.begin(), data.end());

  const auto sort_result = data.at(searched_element);

  ASSERT_EQ(order_stat_random_result, sort_result);
  ASSERT_EQ(order_stat_det_result, sort_result);
}

INSTANTIATE_TEST_CASE_P(Suite, OrderStatisticsFuzzyTest,
                        ::testing::Range(1, 1000));

