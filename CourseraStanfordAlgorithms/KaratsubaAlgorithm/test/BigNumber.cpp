#include <gtest/gtest.h>

#include <array>
#include <string>

#include <BigNumber.hpp>

namespace {
  struct OneStrInputOneStrOutput {
    std::string input;
    std::string output;
  };

    struct TwoStrInputOneBoolOutput {
    std::string first_input;
    std::string second_input;
    bool result;
  };

    struct TwoStrInputOneStrOutput {
    std::string first_input;
    std::string second_input;
    std::string output;
    };
} // namespace


class ConversionTest :
  public ::testing::TestWithParam<OneStrInputOneStrOutput> {
};

TEST_P(ConversionTest, CheckConversion) {
  const auto data = GetParam();

  const BigNumber number (data.input);

  ASSERT_EQ(number.toStr(), data.output);
}

const std::array<OneStrInputOneStrOutput, 6> kConversionTestData = {{
  {"-5", "-5"},
  {"-", "-0"},
  {"-0", "-0"},
  {"", "0"},
  {"0", "0"},
  {"42", "42"},
}};

INSTANTIATE_TEST_CASE_P(DefaultTestSuite, ConversionTest, ::testing::ValuesIn(kConversionTestData));


class ComparisonTest :
  public ::testing::TestWithParam<TwoStrInputOneBoolOutput> {
};

TEST_P(ComparisonTest, CheckComparison) {
  const auto data = GetParam();

  const BigNumber first (data.first_input);
  const BigNumber second (data.second_input);

  ASSERT_EQ(first > second, data.result);
}

const std::array<TwoStrInputOneBoolOutput, 10> kComparisonTestData = {{
  {"-50", "-10", false},
  {"-5", "-10", true},
  {"0", "0", false},
  {"-5", "0", false},
  {"0", "5", false},
  {"-5", "5", false},
  {"5", "-5", true},
  {"1000", "1000", false},
  {"1000", "500", true},
  {"500", "1000", false},
}};

INSTANTIATE_TEST_CASE_P(DefaultTestSuite, ComparisonTest, ::testing::ValuesIn(kComparisonTestData));


class AdditionTest :
  public ::testing::TestWithParam<TwoStrInputOneStrOutput> {
};

TEST_P(AdditionTest, CheckAddition) {
  const auto data = GetParam();

  const BigNumber first (data.first_input);
  const BigNumber second (data.second_input);

  ASSERT_EQ((first + second).toStr(), data.output);
}

const std::array<TwoStrInputOneStrOutput, 4> kAdditionTestData = {{
  {"-20000", "0", "-20000"},
  {"0", "0", "0"},
  {"100", "100", "200"},
  /* {"-20000", "0", "-20000"}, */
  {"-20000", "-2", "-20002"},
}};

INSTANTIATE_TEST_CASE_P(DefaultTestSuite, AdditionTest, ::testing::ValuesIn(kAdditionTestData));
