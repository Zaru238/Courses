#include <fstream>
#include <iostream>
#include <vector>

#include "library/foo.h"

int main() {
  std::ifstream file("IntegerArray.txt");
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

  const auto inversions = count_inversions(data.begin(), data.end());

  std::cout << "Total amount of records is " << data.size() << std::endl;
  std::cout << "Total count of inversions is " << inversions;

  return 0;
}
