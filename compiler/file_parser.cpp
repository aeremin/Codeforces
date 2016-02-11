#include "file_parser.h"

#include <cassert>
#include <fstream>
#include <regex>


namespace {

inline std::string &ltrim(std::string &s) {
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
  return s;
}
inline std::string &rtrim(std::string &s) {
  s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
  return s;
}
inline std::string &trim(std::string &s) {
  return ltrim(rtrim(s));
}

std::regex pragma_once_regex("#pragma +once");
std::regex local_include_regex("#include *\"(.*)\"");
std::regex system_include_regex("#include *<(.*)>");

}  // namespace


ParsedFile parse_file(const std::string& path, const ParserOptions& options, bool is_header) {
  assert(options.strip_comments == false);  // TODO: support
  ParsedFile file;
  std::fstream in(path, std::ios_base::in);
  if (in.fail()) {
    file.problems.push_back({ParsingProblem::Error, -1, "cannot open file"});
    return file;
  }
  std::string line;
  int i_line = -1;
  int pragma_once_count = 0;
  while (std::getline(in, line)) {
    ++i_line;
    size_t old_length = line.length();
    rtrim(line);
    size_t new_length = line.length();
    if (old_length != new_length)
      file.problems.push_back({ParsingProblem::Warning, i_line, "trailing whitespace"});
    std::smatch sm;
    if (std::regex_match(line, sm, pragma_once_regex)) {
      ++pragma_once_count;
    // TODO: Fix includes with comments.
    } else if (std::regex_match(line, sm, local_include_regex)) {
      assert(sm.size() == 2);
      file.local_includes.push_back(sm[1]);
    } else if (std::regex_match(line, sm, system_include_regex)) {
      assert(sm.size() == 2);
      file.system_includes.push_back(sm[1]);
    } else {
      file.code_lines.push_back(line);
    }
  }
  if (is_header) {
    if (pragma_once_count == 0) {
      file.problems.push_back({ParsingProblem::Warning, -1, "no \"#pragma once\" found"});
    } else if (pragma_once_count > 1) {
      file.problems.push_back({ParsingProblem::Warning, -1, "several \"#pragma once\" found"});
    }
  } else {
    if (pragma_once_count > 0) {
      file.problems.push_back({ParsingProblem::Warning, -1, "\"#pragma once\" found in a source_file"});
    }
  }
  return file;
}
