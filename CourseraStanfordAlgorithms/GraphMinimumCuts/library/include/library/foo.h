#pragma once

#include <cstddef>

#include <map>
#include <vector>

namespace graph {
using Vertex = std::size_t;
using AdjacentVertices = std::vector<Vertex>;
using AdjacencyLists = std::map<Vertex, AdjacentVertices>;

std::size_t MinCut(const AdjacencyLists&);
};  // namespace graph
