#include "foo.h"

#include <cassert>
#include <cmath>
#include <cstddef>
#include <cstdlib>

#include <algorithm>
#include <future>
#include <iostream>
#include <limits>
#include <string>
#include <thread>

namespace graph {
namespace {
/* void SanityCheck (const AdjacencyLists& data) { */
/*   auto mutable_data (data); */

/*   for (auto& elem : mutable_data) { */
/*     for (const auto adjacent_vertex : elem.second) { */
/*       auto other_side = mutable_data.find(adjacent_vertex); */
/*       assert(other_side != mutable_data.end()); */
/*       auto other_side_adjacent_vertex = std::find (other_side->second.begin(), */
/*                                                    other_side->second.end(), */
/*                                                    elem.first); */
/*       assert(other_side_adjacent_vertex != other_side->second.end()); */
/*       other_side->second.erase(other_side_adjacent_vertex); */
/*     } */

/*     elem.second.clear(); */
/*   } */
/* } */

std::size_t MinCutAttempt(AdjacencyLists& data) {
  while (data.size() != 2) {

    /* SanityCheck(data); */

    // Select vertex which will be preserved after fusion
    const std::size_t remaining_vertex_pos = std::rand() % data.size();
    auto remaining_vertex_it = std::next(data.begin(), remaining_vertex_pos);
    const auto& remaining_vertex = remaining_vertex_it->first;

    // Select vertex which will be absorbed after fusion
    const std::size_t absorbed_vertex = remaining_vertex_it->second.at(
        std::rand() % remaining_vertex_it->second.size());
    auto absorbed_vertex_it = data.find(absorbed_vertex);
    assert(absorbed_vertex_it != data.end());

    // Copy edges from absorbed vertex to remaining vertex
    // and change adjacent vertices on other side
    for (auto adjacent_vertex : absorbed_vertex_it->second) {
      remaining_vertex_it->second.push_back(adjacent_vertex);

      auto adjacent_vertex_it = data.find(adjacent_vertex);
      assert(adjacent_vertex_it != data.end());

      auto adjacent_vertex_node_it =
          find(adjacent_vertex_it->second.begin(),
               adjacent_vertex_it->second.end(), absorbed_vertex);
      assert(adjacent_vertex_node_it != adjacent_vertex_it->second.end());

      *adjacent_vertex_node_it = remaining_vertex;
    }

    // Remove loop edges
    auto& remaining_adjacents = remaining_vertex_it->second;
    remaining_adjacents.erase(
        std::remove(remaining_adjacents.begin(), remaining_adjacents.end(),
                    remaining_vertex),
        remaining_adjacents.end());

    data.erase(absorbed_vertex_it);
  }

  const auto edges_count = data.begin()->second.size();
  return edges_count;
}

std::size_t MinCutWorker(const AdjacencyLists data,
                         const std::size_t attempts) {
  std::size_t answer = std::numeric_limits<decltype(answer)>::max();

  for (std::size_t i {}; i < attempts; ++i) {
    auto mutable_data {data};
    auto new_answer = MinCutAttempt(mutable_data);
    answer = std::min(answer, new_answer);
    if (!(i % 100)) {
      std::cout << i << "/" << attempts << " answer " << answer << std::endl;
    }
  }

  return answer;
}
};  // namespace

std::size_t MinCut(const AdjacencyLists& data) {
  std::size_t answer = std::numeric_limits<decltype(answer)>::max();

  if (data.size() < 2) {
    return answer;
  }

  const std::size_t workers_count = std::thread::hardware_concurrency();

  const std::size_t attempts_per_job =
      (data.size() * data.size() * std::log(data.size()))/workers_count + 1;


  std::vector<std::future<std::size_t>> results;
  results.reserve(workers_count);

  for (std::size_t i = 0; i < workers_count; ++i) {
    results.push_back(
        std::async(std::launch::async, MinCutWorker, data, attempts_per_job));
  }

  while (!results.empty()) {
    answer = std::min(answer, results.back().get());
    results.pop_back();
  }

  return answer;
}
};  // namespace graph

