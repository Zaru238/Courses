#include "foo.h"

#include <algorithm>
#include <iostream>

namespace {
using DistanceToVertex = std::pair<Vertex, Length>;

class DijkstraShortestPath {
 public:
  DijkstraShortestPath(const Graph& graph, Vertex source, Vertex destination)
      : graph_(graph), source_(source), destination_(destination) {}

  Length Calculate() {
    adjacent_verticies_table_.insert({source_, 0U});
    while (!adjacent_verticies_table_.empty()) {
      const auto closest_point_it = std::min_element(
          adjacent_verticies_table_.begin(), adjacent_verticies_table_.end(),
          [](const auto& l, const auto& r) { return l.second < r.second; });

      const auto closest_point = *closest_point_it;
      adjacent_verticies_table_.erase(closest_point_it);

      AddVertexToProcessedSet(closest_point);
    }

    auto answer_it = processed_verticies_table.find(destination_);
    return answer_it != processed_verticies_table.end() ? answer_it->second
                                                        : kUnconnectedDistance;
  }

 private:
  void AddVertexToProcessedSet(const DistanceToVertex& vertex) {
    processed_verticies_table.insert(vertex);

    for (const auto& edge : graph_.at(vertex.first)) {
      if (processed_verticies_table.find(edge.first) !=
          processed_verticies_table.end()) {
        continue;
      }

      const auto new_distance = vertex.second + edge.second;

      const auto old_distance_it = adjacent_verticies_table_.find(edge.first);

      if (old_distance_it == adjacent_verticies_table_.end()) {
        adjacent_verticies_table_[edge.first] = new_distance;
      } else {
        old_distance_it->second =
            std::min(old_distance_it->second, new_distance);
      }
    }
  }
  const Graph& graph_;
  const Vertex source_;
  const Vertex destination_;
  std::unordered_map<Vertex, Length> processed_verticies_table;
  std::unordered_map<Vertex, Length> adjacent_verticies_table_;
};
}  // namespace

const Length kUnconnectedDistance = 1000000U;

Length FindShortestDistance(const Graph& graph, Vertex source,
                            Vertex destination) {
  DijkstraShortestPath algorithm(graph, source, destination);
  return algorithm.Calculate();
}

