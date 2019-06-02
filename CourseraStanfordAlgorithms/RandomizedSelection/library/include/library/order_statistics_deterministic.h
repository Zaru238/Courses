#pragma once

#include <cassert>
#include <cstddef>

#include <algorithm>
#include <iterator>
#include <type_traits>
#include <vector>

template <typename Iterator>
using Value = typename std::iterator_traits<Iterator>::value_type;

template <typename Iterator>
using Category = typename std::iterator_traits<Iterator>::iterator_category;

template <typename Iterator>
using ValueTable = std::vector<Value<Iterator>>;

template <typename Iterator>
ValueTable<Iterator> ExtractMedianTable(Iterator begin, Iterator end) {
  assert(std::distance(begin, end) > 0);

  ValueTable<Iterator> answer;
  answer.reserve(std::distance(begin, end) / 5);

  while (begin != end) {
    ValueTable<Iterator> block(
        begin,
        std::next(begin, std::min<std::size_t>(5, std::distance(begin, end))));

    std::sort(block.begin(), block.end());
    answer.push_back(block.at((block.size() - 1) / 2));
    begin = std::next(begin, block.size());
  }

  return answer;
}

template <typename Iterator>
Iterator PartionAround(Iterator begin, Iterator end,
                       const Value<Iterator>& pivot_value) {
  assert(std::distance(begin, end) > 0);

  auto i = begin;
  auto j = begin;

  for (; i != end; ++i) {
    if (pivot_value > *i) {
      std::swap(*i, *j);
      ++j;
    }
  }

  return j;
}

template <typename Iterator>
void OrderStatisticsDeterministicH(Iterator begin, Iterator end,
                                       Iterator searched) {
  static_assert(std::is_same_v<Category<Iterator>, std::random_access_iterator_tag>);
  assert((end - begin) > 0);
  assert((searched >= begin) && (end > searched));

  if((begin - end) < 6) {
    std::sort(begin, end);
    return;
  }

  auto median_table = ExtractMedianTable(begin, end);

  const auto median_table_pivot =
      std::next(median_table.begin(), (median_table.size() + 1) / 2);
  OrderStatisticsDeterministicH(median_table.begin(), median_table.end(),
                                median_table_pivot);

  const auto less_end = PartionAround(begin, end, *median_table_pivot);

  if (less_end > searched) {
    OrderStatisticsDeterministicH(begin, less_end, searched);
  } else {
    OrderStatisticsDeterministicH(less_end, end, searched);
  }
}

// See algorithm implementation at Stanford's Algorithm course -
// Deterministic Selection
template <typename Iterator>
Value<Iterator> OrderStatisticsDeterministic(Iterator begin, Iterator end,
                                             size_t searched_pos) {
  assert(std::distance(begin, end) > 0);
  assert(std::distance(begin, end) > searched_pos);

  ValueTable<Iterator> mutable_table (begin, end);
  const auto searched = std::next(mutable_table.begin(), searched_pos);

  OrderStatisticsDeterministicH(mutable_table.begin(), mutable_table.end(),
                                searched);

  return *searched;
}
