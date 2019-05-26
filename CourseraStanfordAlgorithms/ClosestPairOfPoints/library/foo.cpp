#include "foo.h"

#include <cassert>
#include <cmath>

#include <algorithm>
#include <iterator>
#include <limits>

namespace {
Distance CalcDist(const Point& left, const Point& right) {
  const double x_diff = std::abs(left.first - right.first);
  const double y_diff = std::abs(left.second - right.second);

  return std::sqrt(x_diff * x_diff + y_diff * y_diff);
}

Distance FindClosestDistOnStrip (const PointTable& sorted_y,
                                 const Point& pivot, const Distance shortest) {
  Distance answer = shortest;
  PointTable filtered;
  std::copy_if(sorted_y.begin(), sorted_y.end(), std::back_inserter(filtered),
      [&](const auto& a) {
        return ((a.first >= (pivot.first - shortest)) &&
            ((pivot.first + shortest) > a.first));
      });

  if (filtered.size() < 2) {
    return answer;
  }

  for (auto i = filtered.cbegin(); i < filtered.cend(); ++i) {
    auto nearest_end =
        std::next(i, std::min<size_t>(8, std::distance(i, filtered.cend())));
    for (auto j = std::next(i); j != nearest_end; ++j) {
      answer = std::min(answer, CalcDist(*i, *j));
    }
  }
  return answer;
}

Distance FindClosestDivConHelper (const PointTable& sorted_x,
                                  const PointTable& sorted_y) {
  assert(sorted_x.size());
  assert(sorted_x.size() == sorted_y.size());
  if (sorted_x.size() == 1) {
    return std::numeric_limits<Distance>::max();
  }
  if (sorted_x.size() == 2) {
    return CalcDist(sorted_x[0], sorted_x[1]);
  }

  // divide
  const auto pivot = std::next(sorted_x.begin(), sorted_x.size()/2);
  const PointTable left_sorted_x(sorted_x.begin(), pivot);
  const PointTable right_sorted_x(pivot, sorted_x.end());

  PointTable left_sorted_y;
  PointTable right_sorted_y;
  left_sorted_y.reserve(left_sorted_x.size());
  right_sorted_y.reserve(right_sorted_x.size());

  for (const auto& elem : sorted_y) {
    if (elem.first < pivot->first) {
      left_sorted_y.push_back(elem);
    } else if (elem.first > pivot->first) {
      right_sorted_y.push_back(elem);
    } else {
      if (elem.second < pivot->second) {
        left_sorted_y.push_back(elem);
      } else {
        right_sorted_y.push_back(elem);
      }
    }
  }

  // conquer
  const auto left_dist = FindClosestDivConHelper(left_sorted_x, left_sorted_y);
  const auto right_dist = FindClosestDivConHelper(right_sorted_x,
                                                  right_sorted_y);

  const auto shortest_dist = std::min(left_dist, right_dist);
  return FindClosestDistOnStrip(sorted_y, *pivot, shortest_dist);
}
}  // namespace

Distance FindClosestPairBruteforce(const PointTable& table) {
  Distance answer = std::numeric_limits<Distance>::max();
  for (auto i = table.cbegin(); i != table.cend(); ++i) {
    for (auto j = std::next(i); j != table.cend(); ++j) {
      const auto distance = CalcDist(*i, *j);
      answer = std::min(answer, distance);
    }
  }

  return answer;
}

Distance FindClosestPairDivideAndConquer(const PointTable& table) {
  if (table.size() < 2) {
    return std::numeric_limits<Distance>::max();
  }

  auto sorted_by_x (table);
  std::sort(sorted_by_x.begin(), sorted_by_x.end(),
      [](const auto& a, const auto& b) {
        if (a.first != b.first) {
          return a.first < b.first;
        }
        return a.second < b.second;
      });

  auto sorted_by_y (table);
  std::sort(sorted_by_y.begin(), sorted_by_y.end(),
      [](const auto& a, const auto& b) {
        if (a.second != b.second) {
          return a.second < b.second;
        }
        return a.first < b.first;
      });

  return FindClosestDivConHelper(sorted_by_x, sorted_by_y);
}
