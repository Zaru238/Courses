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
  std::transform(std::begin(letters), std::end(letters), std::back_inserter(number_),
    [](const auto letter) {
      return toInt(letter);
    }
  );
}

std::string BigNumber::toStr() const {
  std::string answer;
  answer.reserve(std::size(number_));

  std::transform(std::begin(number_), std::end(number_), std::back_inserter(answer),
    [](const auto integer) {
      return toChar(integer);
    }
  );

  return answer;
}
