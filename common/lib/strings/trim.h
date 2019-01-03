#pragma once

#include <string>
#include <algorithm>
#include <functional>
#include <cctype>

inline std::string &ltrim(std::string &s) {
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](char c){ return !std::isspace(c); }));
  return s;
}

inline std::string &rtrim(std::string &s) {
  s.erase(std::find_if(s.rbegin(), s.rend(), [](char c){ return !std::isspace(c); }).base(), s.end());
  return s;
}

inline std::string &trim(std::string &s) {
  return ltrim(rtrim(s));
}
