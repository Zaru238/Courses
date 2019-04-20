#include <gtest/gtest.h>

#include <array>
#include <string>

#include <library/BigNumber.hpp>

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
}  // namespace

class ConversionTest
    : public ::testing::TestWithParam<OneStrInputOneStrOutput> {};

TEST_P(ConversionTest, CheckConversion) {
  const auto data = GetParam();

  const BigNumber number(data.input);

  ASSERT_EQ(number.toStr(), data.output);
}

const std::array<OneStrInputOneStrOutput, 6> kConversionTestData = {{
    {"-5", "-5"},
    {"-", "0"},
    {"-0", "0"},
    {"", "0"},
    {"0", "0"},
    {"42", "42"},
}};

INSTANTIATE_TEST_CASE_P(DefaultTestSuite, ConversionTest,
                        ::testing::ValuesIn(kConversionTestData));

class ComparisonTest
    : public ::testing::TestWithParam<TwoStrInputOneBoolOutput> {};

TEST_P(ComparisonTest, CheckComparison) {
  const auto data = GetParam();

  const BigNumber first(data.first_input);
  const BigNumber second(data.second_input);

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

INSTANTIATE_TEST_CASE_P(DefaultTestSuite, ComparisonTest,
                        ::testing::ValuesIn(kComparisonTestData));

class AdditionTest : public ::testing::TestWithParam<TwoStrInputOneStrOutput> {
};

TEST_P(AdditionTest, CheckAddition) {
  const auto data = GetParam();

  const BigNumber first(data.first_input);
  const BigNumber second(data.second_input);

  ASSERT_EQ((first + second).toStr(), data.output);
}

const std::array<TwoStrInputOneStrOutput, 11> kAdditionTestData = {{
    {"0", "0", "0"},
    {"100", "100", "200"},
    {"-20000", "0", "-20000"},
    {"-20000", "-2", "-20002"},
    {"200", "-333", "-133"},
    {"200", "-33", "167"},
    {"200", "-3", "197"},
    {"200", "3", "203"},
    {"200", "33", "233"},
    {"200", "3333", "3533"},
    {"10000", "-9999", "1"},
}};

INSTANTIATE_TEST_CASE_P(DefaultTestSuite, AdditionTest,
                        ::testing::ValuesIn(kAdditionTestData));

class SubtractionTest
    : public ::testing::TestWithParam<TwoStrInputOneStrOutput> {};

TEST_P(SubtractionTest, CheckSubtraction) {
  const auto data = GetParam();

  const BigNumber first(data.first_input);
  const BigNumber second(data.second_input);

  ASSERT_EQ((first - second).toStr(), data.output);
}

const std::array<TwoStrInputOneStrOutput, 4> kSubtractionTestData = {{
    {"0", "0", "0"},
    {"45", "9", "36"},
    {"500", "-9", "509"},
    {"-15", "-20", "5"},
}};

INSTANTIATE_TEST_CASE_P(DefaultTestSuite, SubtractionTest,
                        ::testing::ValuesIn(kSubtractionTestData));

class MultiplicationTest
    : public ::testing::TestWithParam<TwoStrInputOneStrOutput> {};

TEST_P(MultiplicationTest, CheckMultiplication) {
  const auto data = GetParam();

  const BigNumber first(data.first_input);
  const BigNumber second(data.second_input);

  ASSERT_EQ((first * second).toStr(), data.output);
}

const std::array<TwoStrInputOneStrOutput, 11> kMultiplicationTestData = {{
    {"0", "0", "0"},
    {"5", "0", "0"},
    {"4", "3", "12"},
    {"8", "-5", "-40"},
    {"-6", "-7", "42"},
    {"10", "10", "100"},
    {"11", "11", "121"},
    {"254", "384", "97536"},
    {"10", "3843243242343242543234", "38432432423432425432340"},
    {"0", "3843243242343242543234", "0"},
    {"4123423142314312421342314324231432432443243", "42432142314234324321432141324132432143214321", "174965677596488198311255401479299804516125710069385307155777638158145498226713417283003"},
}};

INSTANTIATE_TEST_CASE_P(DefaultTestSuite, MultiplicationTest,
                        ::testing::ValuesIn(kMultiplicationTestData));
