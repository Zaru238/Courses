#pragma once

#include <cassert>

#include <iterator>
#include <optional>
#include <stack>
#include <type_traits>
#include <utility>

enum class Pivot {
  kFirst,
  kLast,
  kMedian,
};

template <typename Iterator>
struct Work{
  Work (Iterator begin, Iterator end)
    : begin(begin)
    , end(end) {}

  Iterator begin;
  Iterator end;
};

template <typename Iterator>
using OptionalWorks = std::pair<std::optional<Work<Iterator>>,
                                std::optional<Work<Iterator>>>;

template <typename Iterator, Pivot PivotKind>
OptionalWorks<Iterator> QuickSortHelper(const Work<Iterator>& work) {
  assert(std::distance(work.begin, work.end) > 1);

  Iterator pivot;
  if constexpr (Pivot::kFirst == PivotKind) {
    pivot = work.begin;
  } else if constexpr (Pivot::kLast == PivotKind) {
    pivot = std::prev(work.end);
  } else if constexpr (Pivot::kMedian == PivotKind) {
    const auto pivot_pos = (std::distance(work.begin, work.end) - 1)/2;
    pivot = std::next(work.begin, pivot_pos);
  } else {
    assert(false);  // Unhandled Pivot Kind
  }

  std::swap (*work.begin, *pivot);
  auto end_less = std::next(work.begin);
  auto end_more = std::next(work.begin);

  for (;end_more != work.end; ++end_more) {
    if(*pivot > *end_more) {
      std::swap(*end_less, *end_more);
      ++end_less;
    }
  }
  std::swap(*work.begin, *std::prev(end_less));

  std::optional<Work<Iterator>> left;
  if (std::distance(work.begin, std::prev(end_less)) > 1) {
    left.emplace(work.begin, std::prev(end_less));
  }
  std::optional<Work<Iterator>> right;
  if (std::distance (end_less, work.end) > 1) {
    right.emplace(end_less, work.end);
  }

  return {left, right};
}

template <typename Iterator, Pivot PivotKind = Pivot::kFirst>
size_t QuickSort(Iterator first, Iterator last) {
  // See implementation in Standford algorithms courses
  // QuickSort Partitioning around a pivor
  size_t comparisons {};
  if (std::distance(first, last) < 2) {
    return comparisons;
  }
  std::stack<Work<Iterator>> works;

  Work<Iterator> first_work {first, last};
  works.push(first_work);
  while (!works.empty()) {
    const auto work = works.top();
    comparisons += std::distance(work.begin, work.end) - 1;
    works.pop();
    auto [left, right] = QuickSortHelper<Iterator, PivotKind>(work);
    if (left) {
      works.push(*left);
    }
    if (right) {
      works.push(*right);
    }
  }

  return comparisons;
}
