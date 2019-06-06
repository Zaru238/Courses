#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "library/foo.h"


namespace {
  const std::string kDataFileName {"kargerMinCut.txt"};
}

int main(int argc, char** argv) {
  const auto exe_dir =
      std::filesystem::absolute(std::filesystem::path(argv[0])).parent_path();
  const auto data_file = exe_dir/kDataFileName;
  std::ifstream file(data_file);
  if (!file) {
    std::cerr << "Cannot open file";
    return 0;
  }

  graph::AdjacencyLists data;

  std::string line;
  while (std::getline(file, line)) {
    std::istringstream line_stream (line);

    graph::Vertex vertex {};
    graph::AdjacentVertices adjacent_vertices;

    line_stream >> vertex;

    std::copy(std::istream_iterator<graph::Vertex>(line_stream),
              std::istream_iterator<graph::Vertex>(),
              std::back_inserter(adjacent_vertices));

    if (!line_stream.eof()) {
      std::cerr << "Error during reading file";
      return 0;
    }

    data.emplace(vertex, adjacent_vertices);
  }

  if (!file.eof()) {
      std::cerr << "Error during reading file";
      return 0;
  }

  const auto answer = graph::MinCut(data);

  std::cout << "Number of edges crossing min cut is " << answer << std::endl;

  return 0;
}
