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
  using NumberTable = std::vector<uint8_t>;

  static bool IsGreater(const NumberTable& left, const NumberTable& right);

  static NumberTable Add(const NumberTable& left, const NumberTable& right);

  //left should be greater or eqaal that right
  static NumberTable Substract(const NumberTable& left, const NumberTable& right);

  bool is_positive_;
  // each cell contains one number from 0 to 9
  // variable stores number in little endian (e.g. leftmost cell (0) contains the lowest digit
  NumberTable number_table_;
};
