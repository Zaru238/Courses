#include <BigNumber.hpp>

#include <cassert>
#include <cmath>

#include <algorithm>
#include <array>
#include <iterator>

namespace {

constexpr uint8_t kASCII_DigitShift = 48;
__attribute__((unused)) constexpr uint8_t kDigitCount = 10;

__attribute__((unused)) bool IsNumber(const char letter) {
  return ((kASCII_DigitShift <= letter) &&
          (letter <= (kASCII_DigitShift + kDigitCount)));
}

__attribute__((unused)) bool IsNumber(const std::string& letters) {
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
  assert(integer <= 9);
  return (integer + kASCII_DigitShift);
}
}  // namespace

BigNumber::BigNumber(const std::string& letters) : is_positive_{true} {
  assert(IsNumber(letters));

  auto lastLetterIter = std::crend(letters);

  if (!letters.empty() && (*(lastLetterIter - 1) == '-')) {
    is_positive_ = false;
    --lastLetterIter;
  }

  if (std::crbegin(letters) == lastLetterIter) {
    number_table_.push_back(0);
  } else {
    number_table_.reserve(std::size(letters));
    std::transform(std::crbegin(letters), lastLetterIter,
                   std::back_inserter(number_table_),
                   [](const auto letter) { return toInt(letter); });
  }

  Adjust();
}

bool BigNumber::operator>(const BigNumber& other) const {
  if (is_positive_ && !other.is_positive_) {
    return true;
  }

  if (!is_positive_ && other.is_positive_) {
    return false;
  }

  bool is_greater_inmodulus{false};

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
    if (IsGreater(number_table_, other.number_table_)) {
      answer.number_table_ = Substract(number_table_, other.number_table_);
      answer.is_positive_ = is_positive_;
    } else {
      answer.number_table_ = Substract(other.number_table_, number_table_);
      answer.is_positive_ = other.is_positive_;
    }
  }

  answer.Adjust();

  return answer;
}

BigNumber BigNumber::operator-(const BigNumber& other) const {
  BigNumber negative_other{other};
  negative_other.is_positive_ = !other.is_positive_;

  return this->operator+(negative_other);
}

// see algorithm description at
// https://en.wikipedia.org/wiki/Karatsuba_algorithm
BigNumber BigNumber::operator*(const BigNumber& other) const {
  BigNumber answer("0");
  answer.is_positive_ = (is_positive_ == other.is_positive_);

  const size_t max_length =
      std::max(std::size(number_table_), std::size(other.number_table_));

  if (1 == max_length) {
    const uint8_t product = number_table_.at(0) * other.number_table_.at(0);
    answer.number_table_.resize(2);
    answer.number_table_.at(0) = product % 10;
    answer.number_table_.at(1) = product / 10;
    answer.Adjust();
  } else {
    const size_t digit_shift = (max_length / 2) + (max_length % 2);

    const auto get_lower_part = [=](const BigNumber& number) -> BigNumber {
      const auto& in_table = number.number_table_;
      BigNumber answer("0");

      const auto left_iter = std::begin(in_table);
      const auto right_iter = std::next(
          std::begin(in_table), std::min(std::size(in_table), digit_shift));

      answer.number_table_ = NumberTable(left_iter, right_iter);
      answer.Adjust();

      return answer;
    };

    const auto get_higher_part = [=](const BigNumber& number) -> BigNumber {
      const auto& in_table = number.number_table_;
      BigNumber answer("0");

      const auto left_iter = std::next(
          std::begin(in_table), std::min(std::size(in_table), digit_shift));
      const auto right_iter = std::next(
          std::begin(in_table), std::min(std::size(in_table), digit_shift * 2));

      answer.number_table_ = NumberTable(left_iter, right_iter);
      answer.Adjust();

      return answer;
    };

    const BigNumber x0 = get_lower_part(*this);
    const BigNumber x1 = get_higher_part(*this);
    const BigNumber y0 = get_lower_part(other);
    const BigNumber y1 = get_higher_part(other);

    const BigNumber z0 = x0 * y0;
    const BigNumber z2 = x1 * y1;
    const BigNumber z1 = ((x0 + x1) * (y0 + y1)) - z0 - z2;

    answer = z2.ShiftToRightByN(digit_shift * 2) +
             z1.ShiftToRightByN(digit_shift) + z0;
  }

  return answer;
}

std::string BigNumber::toStr() const {
  std::string answer;

  if (!is_positive_) {
    answer.push_back('-');
  }

  answer.reserve(std::size(answer) + std::size(number_table_));

  std::transform(std::crbegin(number_table_), std::crend(number_table_),
                 std::back_inserter(answer),
                 [](const auto integer) { return toChar(integer); });

  return answer;
}

void BigNumber::Adjust() {
  while ((std::size(number_table_) > 1) && (number_table_.back() == 0)) {
    number_table_.pop_back();
  }

  if ((std::size(number_table_) == 1) && (number_table_.at(0) == 0) &&
      !is_positive_) {
    is_positive_ = true;
  }
}

BigNumber BigNumber::ShiftToRightByN(size_t n) const {
  BigNumber answer(*this);

  if ((std::size(answer.number_table_) == 1) &&
      (answer.number_table_.at(0) == 0)) {
    return answer;
  }

  answer.number_table_.insert(std::begin(answer.number_table_), n, 0);

  return answer;
}

bool BigNumber::IsGreater(const NumberTable& left, const NumberTable& right) {
  bool answer{false};

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

BigNumber::NumberTable BigNumber::Add(const NumberTable& left,
                                      const NumberTable& right) {
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

  return answer;
}

BigNumber::NumberTable BigNumber::Substract(const NumberTable& left,
                                            const NumberTable& right) {
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

  return answer;
}
