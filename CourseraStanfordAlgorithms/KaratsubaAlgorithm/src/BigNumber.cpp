#include <BigNumber.hpp>

#include <algorithm>
#include <array>
#include <cassert>
#include <iterator>

namespace {

  constexpr uint8_t kASCII_DigitShift = 48;
  __attribute__((unused))
  constexpr uint8_t kDigitCount = 10;

  __attribute__((unused))
  bool IsNumber(const char letter) {
    return ((kASCII_DigitShift <= letter) && (letter <= (kASCII_DigitShift + kDigitCount)));
  }

  __attribute__((unused))
  bool IsNumber(const std::string& letters) {
    for (const auto& letter : letters) {
      if (!IsNumber(letter)) {
        return false;
      }
    }

    return true;
  }

  uint8_t toInt(const char digit) {
    assert(IsNumber(digit));
    return (digit - kASCII_DigitShift);
  }

  char toChar(const uint8_t integer) {
    assert (integer <= 9);
    return (integer + kASCII_DigitShift);
  }
}

BigNumber::BigNumber(const std::string& letters) {
  assert(IsNumber(letters));

  number_.reserve(std::size(letters));
  std::transform(std::crbegin(letters), std::crend(letters), std::back_inserter(number_),
    [](const auto letter) {
      return toInt(letter);
    }
  );
}

bool BigNumber::operator>(const BigNumber& other) const {
  if (is_positive && !other.is_positive) {
    return true;
  }

  if (!is_positive && other.is_positive) {
    return false;
  }

  bool is_greater_inmodulus {false};

  if (std::size(number_) > std::size(other.number_)) {
    is_greater_inmodulus = true;
  } else if (std::size(other.number_) > std::size(number_)) {
    is_greater_inmodulus = false;
  } else {
    for (size_t i = std::size(number_); i > 0; --i) {
      if (number_.at(i - 1) > other.number_.at(i - 1)) {
        is_greater_inmodulus = true;
        break;
      } else if (other.number_.at(i - 1) > number_.at(i - 1)) {
        is_greater_inmodulus = false;
        break;
      }
    }
  }

  return (is_positive && is_greater_inmodulus);
}

BigNumber BigNumber::operator+(const BigNumber& other) const {
  const size_t addOpCount = std::max(std::size(number_), std::size(other.number_));
  BigNumber answer("");
  answer.number_.resize(addOpCount + 1, 0);

  for (size_t i = 0; i < addOpCount; ++i) {
    const uint8_t sum = answer.number_.at(i) + number_.at(i) + other.number_.at(i);
    answer.number_.at(i) = sum % 10;
    answer.number_.at(i + 1) += sum / 10;
  }

  if (0 == answer.number_.back()) {
    answer.number_.pop_back();
  }

  return answer;
}


std::string BigNumber::toStr() const {
  if (std::empty(number_)) {
    return std::string(0);
  }

  std::string answer;
  answer.reserve(std::size(number_));

  std::transform(std::crbegin(number_), std::crend(number_), std::back_inserter(answer),
    [](const auto integer) {
      return toChar(integer);
    }
  );

  return answer;
}
