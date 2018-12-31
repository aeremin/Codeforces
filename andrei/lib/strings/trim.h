#pragma once

#include <string>
#include <algorithm>
#include <functional>
#include <cctype>

inline std::string &ltrim(std::string &s) {
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not_fn(std::isspace)));
  return s;
}

inline std::string &rtrim(std::string &s) {
  s.erase(std::find_if(s.rbegin(), s.rend(), std::not_fn(std::isspace)).base(), s.end());
  return s;
}

inline std::string &trim(std::string &s) {
  return ltrim(rtrim(s));
}
