#include <gtest/gtest.h>

#include <iostream>

#include <BigNumber.hpp>

TEST(Foo, DefaultCase) {
  BigNumber number(std::string("42"));
  ASSERT_EQ(std::string("42"), number.toStr());
}
