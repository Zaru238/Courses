#include <BigNumber.hpp>

#include <cassert>
#include <cmath>

#include <algorithm>
#include <array>
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
    if (letters.empty()) {
      return true;
    }

    auto iter = cbegin(letters);

    if (*iter == '-') {
      ++iter;
    }

    for (; iter != std::cend(letters); ++iter) {
      if (!IsNumber(*iter)) {
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

BigNumber::BigNumber(const std::string& letters)
    : is_positive_{true}{
  assert(IsNumber(letters));

  auto lastLetterIter = std::crend(letters);

  if (!letters.empty() && (*(lastLetterIter - 1) == '-')) {
    is_positive_ = false;
    --lastLetterIter;
  }

  if (std::crbegin(letters) == lastLetterIter) {
    number_table_.push_back(0);
    return;
  }

  number_table_.reserve(std::size(letters));
  std::transform(std::crbegin(letters), lastLetterIter, std::back_inserter(number_table_),
    [](const auto letter) {
      return toInt(letter);
    }
  );
}

bool BigNumber::operator>(const BigNumber& other) const {
  if (is_positive_ && !other.is_positive_) {
    return true;
  }

  if (!is_positive_ && other.is_positive_) {
    return false;
  }

  bool is_greater_inmodulus {false};

  if (std::size(number_table_) > std::size(other.number_table_)) {
    is_greater_inmodulus = true;
  } else if (std::size(other.number_table_) > std::size(number_table_)) {
    is_greater_inmodulus = false;
  } else {
    for (size_t i = std::size(number_table_); i > 0; --i) {
      if (number_table_.at(i - 1) > other.number_table_.at(i - 1)) {
        is_greater_inmodulus = true;
        break;
      } else if (other.number_table_.at(i - 1) > number_table_.at(i - 1)) {
        is_greater_inmodulus = false;
        break;
      }
    }
  }

  return (is_positive_ == is_greater_inmodulus);
}

BigNumber BigNumber::operator+(const BigNumber& other) const {
  BigNumber answer("");

  if (is_positive_ == other.is_positive_) {
    answer.number_table_ = Add(number_table_, other.number_table_);
    answer.is_positive_ = other.is_positive_;
  } else {
    if (number_table_ > other.number_table_) {
      answer.number_table_ = Substract(number_table_, other.number_table_);
      answer.is_positive_ = is_positive_;
    } else {
      answer.number_table_ = Substract(other.number_table_, number_table_);
      answer.is_positive_ = other.is_positive_;
    }
  }

  return answer;
}

std::string BigNumber::toStr() const {
  std::string answer;

  if (!is_positive_) {
    answer.push_back('-');
  }

  answer.reserve(std::size(answer) + std::size(number_table_));

  std::transform(std::crbegin(number_table_), std::crend(number_table_), std::back_inserter(answer),
    [](const auto integer) {
      return toChar(integer);
    }
  );

  return answer;
}

bool BigNumber::IsGreater(const NumberTable& left, const NumberTable& right) {
  bool answer {false};

  if (std::size(left) != std::size(right)) {
    answer = std::size(left) > std::size(right);
  } else {
    auto left_iter = std::crbegin(left);
    auto right_iter = std::crbegin(right);
    for (size_t i = 0; i < std::size(left); ++i) {
      if (*(left_iter + i) != *(right_iter + i)) {
        answer = *(left_iter + i) > *(right_iter + i);
        break;
      }
    }
  }

  return answer;
}

BigNumber::NumberTable BigNumber::Add(const NumberTable& left, const NumberTable& right) {
  const size_t add_op_count = std::max(std::size(left), std::size(right));
  NumberTable answer;
  answer.resize(add_op_count + 1, 0);

  for (size_t i = 0; i < add_op_count; ++i) {
    const uint8_t left_term = std::size(left) > i ? left.at(i) : 0;
    const uint8_t right_term = std::size(right) > i ? right.at(i) : 0;
    const uint8_t sum = answer.at(i) + left_term + right_term;
    answer.at(i) = sum % 10;
    answer.at(i + 1) += sum / 10;
  }

  if (0 == answer.back()) {
    answer.pop_back();
  }

  return answer;
}

BigNumber::NumberTable BigNumber::Substract(const NumberTable& left, const NumberTable& right) {
  const size_t sub_op_count = std::size(left);
  NumberTable answer;
  answer.resize(sub_op_count + 1, 0);

  uint8_t carry = 0;
  for (size_t i = 0; i < sub_op_count; ++i) {
    const uint8_t left_term = left.at(i);
    const uint8_t right_term = std::size(right) > i ? right.at(i) : 0;
    if ((left_term - right_term - carry) < 0) {
      answer.at(i) = 10 + left_term - right_term - carry;
      carry = 1;
    } else {
      answer.at(i) = left_term - right_term - carry;
      carry = 0;
    }
  }

  while ((answer.back() == 0) && (std::size(answer) != 1)) {
    answer.pop_back();
  }

  return NumberTable();
}


