#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "library/foo.h"

namespace {
  const std::string kDataFileName {"QuickSort.txt"};
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

  std::vector<ssize_t> data;

  ssize_t number {};
  while (1) {
    file >> number;

    if (file.eof()) {
      break;
    }

    if (file.fail()) {
      std::cerr << "Error during reading file";
      return 0;
    }

    data.push_back(number);
  }

  auto second_data(data);
  auto third_data(data);

  using Iter = decltype(data)::iterator;
  const auto first_pivot_comp =
      QuickSort<Iter, Pivot::kFirst>(data.begin(), data.end());
  const auto last_pivot_comp =
      QuickSort<Iter, Pivot::kLast>(second_data.begin(), second_data.end());
  const auto median_pivot_comp =
      QuickSort<Iter, Pivot::kMedian>(third_data.begin(), third_data.end());

  std::cout << "Pivot is a first element " << first_pivot_comp << std::endl;
  std::cout << "Pivot is a last element " << last_pivot_comp << std::endl;
  std::cout << "Pivot is a median element " << median_pivot_comp << std::endl;

  return 0;
}
