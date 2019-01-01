// Matcher for solution tests.
//
// * EqualsTrimmed(expected)
//   Returns if argument is equal to expected value if:
//     - both are stripped of leading and trailing whitespace.
//   Convenient to use with raw string literals, e.g.
//   `  EXPECT_THAT(glider, EqualsTrimmed(R"(
//   `.X.
//   `..X
//   `XXX
//   `  )"));
//
// * EqualsFuzzy
//   Returns if argument is equal to expected value if:
//     - both are stripped of leading and trailing whitespace;
//     - all double values are compared with relative precision of 1e-7.
//   Sample usage:
//   `  EXPECT_THAT("1000000000", Not(EqualsFuzzy("1000000001")));
//   `  EXPECT_THAT("1000000000.0", EqualsFuzzy("1000000001.0"));

#pragma once

#include <regex>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "strings/trim.h"
#include "util/check.h"


namespace {
[[maybe_unused]] bool fuzzy_compare(double expected, double arg) {
  return std::abs(arg - expected) / std::max(1., expected) < 1e-7;
}
}  // namespace

MATCHER_P(EqualsTrimmed, expected, "") {
  std::string arg_str = arg;
  std::string expected_str = expected;
  trim(arg_str);
  trim(expected_str);
  return arg_str == expected_str;
}

// NOTE. Doesn't support numbers without leading zero (e.g. ".1") and
//       scientific format (e.g. "6.022e23")
MATCHER_P(EqualsFuzzy, expected, "") {
  std::regex float_regex(R"([+-]?[0-9]+\.[0-9]*)");
  std::string arg_str = arg;
  std::string expected_str = expected;
  trim(arg_str);
  trim(expected_str);
  auto arg_it = arg_str.begin();
  auto expected_it = expected_str.begin();
  while (arg_it != arg_str.end() && expected_it != expected_str.end()) {
    {
      auto is_space = [](char c){ return std::isspace(c); };
      auto arg_non_ws_it = std::find_if(arg_it, arg_str.end(), is_space);
      auto expected_non_ws_it = std::find_if(expected_it, expected_str.end(), is_space);
      std::string arg_token(arg_it, arg_non_ws_it);
      std::string expected_token(expected_it, expected_non_ws_it);
      std::smatch sm;
      if (std::regex_match(arg_token, sm, float_regex) && std::regex_match(expected_token, sm, float_regex)) {
        double arg_value = 0., expected_value = 0.;
        int arg_len = 0, expected_len = 0;
        sscanf(arg_token.c_str(), "%lf%n", &arg_value, &arg_len);
        sscanf(expected_token.c_str(), "%lf%n", &expected_value, &expected_len);
        CHECK(arg_len == int(arg_token.length()));
        CHECK(expected_len == int(expected_token.length()));
        if (!fuzzy_compare(expected_value, arg_value))
          return false;
      }
      else if (arg_token != expected_token)
        return false;
      arg_it = arg_non_ws_it;
      expected_it = expected_non_ws_it;
    }
    {
      auto is_not_space = [](char c){ return !std::isspace(c); };
      auto arg_ws_it = std::find_if(arg_it, arg_str.end(), is_not_space);
      auto expected_ws_it = std::find_if(expected_it, expected_str.end(), is_not_space);
      std::string arg_token(arg_it, arg_ws_it);
      std::string expected_token(expected_it, expected_ws_it);
      if (arg_token != expected_token)
        return false;
      arg_it = arg_ws_it;
      expected_it = expected_ws_it;
    }
  }
  return arg_it == arg_str.end() && expected_it == expected_str.end();
}

#define EXPECT_EQ_TRIMMED(a, b) \
  EXPECT_THAT(a, EqualsTrimmed(b))

#define EXPECT_EQ_FUZZY(a, b) \
  EXPECT_THAT(a, EqualsFuzzy(b))
