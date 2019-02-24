#pragma once

#include <string>
#include <vector>

class BigNumber {
public:
  explicit BigNumber(const std::string& number);

  BigNumber(const BigNumber&) = delete;
  BigNumber(BigNumber&&) = delete;

  //BigNumber operator*(const BigNumber&) const;

  std::string toStr() const;

private:
  // each cell contains one number from 0 to 9
  // variable stores number in big endian (e.g. leftmost cell (0) contains the leftmost digit
  std::vector<uint8_t> number_;
};
