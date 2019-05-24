#include <cstddef>
#include <cstdlib>

#include <iostream>

#include <gtest/gtest.h>

#include <library/foo.h>

class StrassenAlgorithmTest
    : public ::testing::TestWithParam<int> {};


TEST_P(StrassenAlgorithmTest, RandomMatrixTest) {
  using MatrixType = Matrix<12>;
  MatrixType left;
  decltype(left)::DataType left_data;
  for(auto& elem : left_data) {
    elem = std::rand() % 100;
  }
  left.set_data(left_data);
  std::cout << "Left matrix" << std::endl;
  left.print();

  MatrixType right;
  decltype(left)::DataType right_data;
  for(auto& elem : right_data) {
    elem = std::rand() % 100;
  }
  right.set_data(right_data);
  std::cout << " Right matrix" << std::endl;
  right.print();

  const auto default_answer = left.standart_multiply(right);
  const auto default_answer_data = default_answer.get_data();
  std::cout << "Brute force algorithm" << std::endl;
  default_answer.print();

  const auto strassen_answer = left.strassen_multiply(right);
  const auto strassen_answer_data = strassen_answer.get_data();
  std::cout << "Strassen algorithm" << std::endl;
  strassen_answer.print();

  ASSERT_EQ(default_answer_data, strassen_answer_data);
}

INSTANTIATE_TEST_CASE_P(Suite, StrassenAlgorithmTest, ::testing::Range(1, 1000));
