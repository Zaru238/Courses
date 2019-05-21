#pragma once

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>


template <class Iter>
ssize_t count_inversion_helper(Iter first, Iter last) {
  ssize_t inversions{};
  const auto dist = std::distance(first, last);

  if (2 > dist) {
    return inversions;
  }

  // Divide and process
  Iter midst = std::next(first, dist/2);
  inversions += count_inversion_helper(first, midst);
  inversions += count_inversion_helper(midst, last);

  //Calculate inversions
  const std::vector<typename std::iterator_traits<Iter>::value_type>
      left_sorted {first, midst};
  const std::vector<typename std::iterator_traits<Iter>::value_type>
      right_sorted (midst, last);

  auto left_iter = std::cbegin(left_sorted);
  auto right_iter = std::cbegin(right_sorted);
  size_t left_elements_left = dist/2;

  while((std::cend(left_sorted) != left_iter) &&
      (std::cend(right_sorted) != right_iter)) {
    if (*left_iter < *right_iter) {
      *first = *left_iter;
      left_iter = std::next(left_iter);
      --left_elements_left;
    } else {
      *first = *right_iter;
      right_iter = std::next(right_iter);
      inversions += left_elements_left;
    }
    first = std::next(first);
  }

  if (std::cend(left_sorted) != left_iter) {
    std::copy(left_iter, std::cend(left_sorted), first);
  } else {
    std::copy(right_iter, std::cend(right_sorted), first);
  }

  return inversions;
}

// Doesn't alter input data
template <class Iter>
ssize_t count_inversions(Iter first, Iter last) {
  std::vector<typename std::iterator_traits<Iter>::value_type> data(first,
                                                                    last);
  return count_inversion_helper(std::begin(data), std::end(data));
}
