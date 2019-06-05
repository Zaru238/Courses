#include <filesystem>
#include <fstream>
#include <iostream>
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

  return 0;
}
