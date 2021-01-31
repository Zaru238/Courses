#pragma once

#include <unordered_map>
#include <utility>
#include <vector>

using Vertex = std::size_t;
using Length = std::size_t;
using Edge = std::pair<Vertex, Length>;
using Graph = std::unordered_map<Vertex, std::vector<Edge>>;

extern const Length kUnconnectedDistance;

Length FindShortestDistance(const Graph& graph, Vertex source, Vertex destination);
