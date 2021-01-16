#include <exception>
#include <fstream>
#include <iostream>
#include <string>

#include "library/foo.h"

using namespace std::string_literals;

const auto kArkFile = "arks.txt";
constexpr auto kVertexCount = 875714U;
const auto kVertexShift = 1U;

int main() {
  Graph graph(kVertexCount);

  {
    std::ifstream arks(kArkFile);

    if (!arks.good()) {
      std::cerr << "Cannot open ark file" << std::endl;
      return -1;
    }

    std::size_t tail{};
    std::size_t head{};

    while (arks >> tail >> head) {
      graph.at(tail - kVertexShift).push_back(head - kVertexShift);
    }
  }

  const auto answer = FindSCCs(graph);

  std::cout <<" Answer is";
  for (auto scc_size: answer) {
    std::cout <<" " << scc_size;
  }
  std::cout << std::endl;

  return 0;
}
