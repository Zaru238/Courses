#include "foo.h"

#include <assert.h>

#include <algorithm>
#include <iostream>
#include <numeric>
#include <stack>

class OrderCalculator {
 public:
  OrderCalculator(const Graph& graph)
      : graph_(graph), ordering_(), visited_verticies_(graph_.size()) {}

  std::vector<size_t> Calculate() {
    for (std::size_t i = 0U; i < graph_.size(); ++i) {
      if (!visited_verticies_.at(i)) {
        visited_verticies_.at(i) = true;
        processVertex(i);
      }
    }

    return std::vector<std::size_t>(ordering_.rbegin(), ordering_.rend());
  }

 private:
  void processVertex(Vertex vertex) {
    for (auto head : graph_.at(vertex)) {
      if (!visited_verticies_.at(head)) {
        visited_verticies_.at(head) = true;
        processVertex(head);
      }
    }

    ordering_.push_back(vertex);
  }

  const Graph& graph_;
  std::vector<std::size_t> ordering_;
  std::vector<bool> visited_verticies_;
};

class SCCCalculator {
 public:
  SCCCalculator(const Graph& graph, const std::vector<std::size_t>& ordering)
      : graph_(graph), ordering_(ordering), visited_verticies_(graph.size()) {}

  std::vector<std::vector<Vertex>> calculate() {
    std::vector<std::vector<Vertex>> answer;
    for (auto i = 0U; i < ordering_.size(); ++i) {
      const auto processing = ordering_.at(i);
      if (visited_verticies_.at(processing)) {
        continue;
      }

      visited_verticies_.at(processing) = true;
      answer.push_back(DFS(processing));
    }

    return answer;
  }

 private:
  std::vector<Vertex> DFS(Vertex vertex) {
    std::vector<Vertex> answer;

    std::stack<Vertex> verticies_to_visit;
    verticies_to_visit.push(vertex);

    while (!verticies_to_visit.empty()) {
      const auto processing = verticies_to_visit.top();
      verticies_to_visit.pop();
      answer.push_back(processing);

      for (auto head : graph_.at(processing)) {
        if (!visited_verticies_.at(head)) {
          visited_verticies_.at(head) = true;
          verticies_to_visit.push(head);
        }
      }
    }

    return answer;
  }
  const Graph& graph_;
  const std::vector<std::size_t>& ordering_;
  std::vector<bool> visited_verticies_;
};

std::vector<std::size_t> FindSCCs(const Graph& graph) {
  // 1. Create reversed graph
  Graph reversed_graph(graph.size());

  for (std::size_t tail = 0; tail < graph.size(); ++tail) {
    const auto tail_table = graph.at(tail);
    for (auto head : tail_table) {
      reversed_graph.at(head).push_back(tail);
    }
  }

  assert(reversed_graph.size() == graph.size());

  // 2. Create ordering table
  OrderCalculator order_calculator(reversed_graph);
  const auto ordering = order_calculator.Calculate();

  assert(ordering.size() == graph.size());

  // 3. Calculate SCCs
  SCCCalculator sccc_calculator(graph, ordering);
  const auto sccc = sccc_calculator.calculate();

  std::vector<std::size_t> scc_sizes;
  scc_sizes.reserve(sccc.size());

  for (const auto& scc : sccc) {
    scc_sizes.push_back(scc.size());
  }

#ifndef NDEBUG
  const auto total_scc_verticies =
      std::accumulate(scc_sizes.begin(), scc_sizes.end(), 0U);

  assert(total_scc_verticies == graph.size());
#endif

  std::sort(scc_sizes.rbegin(), scc_sizes.rend());
  scc_sizes.resize(5);

  return scc_sizes;
}
