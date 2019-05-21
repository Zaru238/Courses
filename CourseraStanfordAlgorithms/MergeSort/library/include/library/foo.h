#pragma once

#include <algorithm>
#include <iostream>
#include <vector>

template <class Iter>
void merge_sort(Iter first, Iter last) {
  const auto dist = std::distance(first, last);

  if (2 > dist) {
    return;
  }

  // Divide and sort each part
  Iter midst = std::next(first, dist/2);
  merge_sort(first, midst);
  merge_sort(midst, last);

  // Merge
  const std::vector<typename std::iterator_traits<Iter>::value_type>
      left_sorted {first, midst};
  const std::vector<typename std::iterator_traits<Iter>::value_type>
      right_sorted (midst, last);

  auto left_iter = std::cbegin(left_sorted);
  auto right_iter = std::cbegin(right_sorted);

  while((std::cend(left_sorted) != left_iter) &&
      (std::cend(right_sorted) != right_iter)) {
    if (*left_iter < *right_iter) {
      *first = *left_iter;
      left_iter = std::next(left_iter);
    } else {
      *first = *right_iter;
      right_iter = std::next(right_iter);
    }
    first = std::next(first);
  }

  if (std::cend(left_sorted) != left_iter) {
    std::copy(left_iter, std::cend(left_sorted), first);
  } else {
    std::copy(right_iter, std::cend(right_sorted), first);
  }
}

