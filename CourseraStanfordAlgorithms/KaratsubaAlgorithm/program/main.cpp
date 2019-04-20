#include <iostream>

#include "library/BigNumber.hpp"

int main() {
  const BigNumber left(
      "3141592653589793238462643383279502884197169399375105820974944592");
  const BigNumber right(
      "2718281828459045235360287471352662497757247093699959574966967627");

  std::cout << (left * right).toStr() << std::endl;
  return 0;
}
