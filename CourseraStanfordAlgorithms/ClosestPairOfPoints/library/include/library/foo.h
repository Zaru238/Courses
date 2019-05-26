#pragma once

#include <vector>
#include <utility>

using Distance = double;
// first -x, second -y
using Point = std::pair<double, double>;
using PointTable = std::vector<Point>;

Distance FindClosestPairBruteforce(const PointTable&);
Distance FindClosestPairDivideAndConquer(const PointTable&);
