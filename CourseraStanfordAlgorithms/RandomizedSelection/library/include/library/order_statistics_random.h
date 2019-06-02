#pragma once

#include <cassert>
#include <cstddef>
#include <cstdlib>

#include <algorithm>
#include <iterator>
#include <vector>
#include <utility>

template <typename Iterator>
Iterator OrderStatisticsRandomH(Iterator begin, Iterator end,
                                 Iterator holds_value) {
  assert(std::distance(begin, end) > std::distance(begin, holds_value));
  if (std::distance(begin, end) == 1) {
    return begin;
  }

  std::swap(*begin, *holds_value);

  Iterator i = std::next(begin);
  Iterator j = std::next(begin);

  for (; i != end; ++i) {
    if (*begin >= *i) {
      std::swap(*i, *j);
      ++j;
    }
 }

  std::swap(*begin, *std::prev(j));

  return std::prev(j);
}

template <typename Iterator>
typename std::iterator_traits<Iterator>::value_type OrderStatisticsRandom(
    Iterator begin, Iterator end, size_t required_pos) {
  assert(std::distance(begin, end) > required_pos);
  if (std::distance(begin, end) == 1) {
    return *begin;
  }

  std::vector<typename std::iterator_traits<Iterator>::value_type> data(begin,
                                                                        end);

  const auto required = std::next(data.begin(), required_pos);
  auto span_begin = data.begin();
  auto span_end = data.end();
  while (1) {
    const size_t unsorted_pivot_shift =
        std::rand() % (std::distance(span_begin, span_end));

    auto holds_value = std::next(span_begin, unsorted_pivot_shift);

    const auto pivot = OrderStatisticsRandomH(
        span_begin, span_end, holds_value);

    if (required < pivot) {
      span_end = pivot;
    } else if (required > pivot) {
      span_begin = std::next(pivot);
    } else {
      break;
    }

    assert((required >= span_begin) && (span_end > required));
  }

  return *required;
}

