#include <gtest/gtest.h>

#include <iostream>

#include <BigNumber.hpp>

TEST(BigNumber, IOTest) {
  const BigNumber number(std::string("42"));
  ASSERT_EQ(number.toStr(), std::string("42"));
}

TEST(BigNumber, AdditionTest) {
  const BigNumber term ("1024");
  const BigNumber answer = term + term;
  ASSERT_EQ(answer.toStr(), std::string ("2048"));
}
