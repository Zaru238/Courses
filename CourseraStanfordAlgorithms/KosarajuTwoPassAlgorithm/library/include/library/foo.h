#pragma once

#include <cstdint>
#include <vector>

using Vertex = std::size_t;
using Graph = std::vector<std::vector<Vertex>>;

std::vector<std::size_t> FindSCCs(const Graph&);
