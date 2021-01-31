#include <array>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "library/foo.h"

const auto kGraphFileName = "edges";

int main() {
  std::ifstream graph_file(kGraphFileName);

  if (!graph_file.good()) {
    std::cerr << "Cannot open graph file" << std::endl;
    return -1;
  }

  Graph graph;

  std::string line;
  while (std::getline(graph_file, line)) {
    std::stringstream line_stream(line);
    Vertex source{};
    line_stream >> source;

    Vertex destination{};
    Length length{};
    std::vector<Edge> edge_table;

    while (line_stream >> destination && line_stream.ignore(1) &&
           line_stream >> length) {
      edge_table.push_back(std::make_pair(destination, length));
    }

    graph[source] = std::move(edge_table);
  }

  const Vertex kSource = 1U;
  const std::array<Vertex, 10U> kDestinationTable{7,   37,  59,  82,  99,
                                                  115, 133, 165, 188, 197};

  std::vector<Length> shortest_path_table;

  for (auto destination : kDestinationTable) {
    shortest_path_table.push_back(
        FindShortestDistance(graph, kSource, destination));
  }

  std::cout << "Shortest pathes are";
  for (auto shortest_path: shortest_path_table) {
    std:: cout << " " << shortest_path;
  }
  std::cout << std::endl;

  return 0;
}
