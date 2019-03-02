#pragma once

#include <string>
#include <vector>

class BigNumber {
public:
  explicit BigNumber(const std::string& number);

  BigNumber(const BigNumber&) = default;
  BigNumber(BigNumber&&) = default;

  bool operator>(const BigNumber&) const;

  BigNumber operator+(const BigNumber&) const;
  /* BigNumver operator-(const BigNumver&) const; */
  /* BigNumber operator*(const BigNumber&) const; */

  std::string toStr() const;

private:
  // zerron number should have positive sign
  bool is_positive {true};
  // each cell contains one number from 0 to 9
  // variable stores number in little endian (e.g. leftmost cell (0) contains the lowest digit
  std::vector<uint8_t> number_;
};
