#include "file_parser.h"

#include <fstream>
#include <regex>

#include "strings/trim.h"
#include "util/check.h"


namespace {

std::regex pragma_once_regex("#pragma +once");
std::regex local_include_regex("#include *\"(.*)\"");
std::regex system_include_regex("#include *<(.*)>");
std::regex test_start_regex("class (.*)_Test : public SolverTest.*");

}  // namespace


ParsedFile parse_file(const std::string& path, const ParserOptions& options, bool is_header) {
  CHECK(options.strip_comments == false);  // TODO: support
  ParsedFile file;
  std::fstream in(path, std::ios_base::in);
  if (in.fail()) {
    file.problems.push_back({ParsingProblem::Error, -1, "cannot open file"});
    return file;
  }
  std::string line;
  int i_line = -1;
  int pragma_once_count = 0;
  std::string solver_name;
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
      CHECK(sm.size() == 2);
      const std::string include_name = sm[1];
      if (include_name.find("solution_tests/") == std::string::npos)
        file.local_includes.push_back(include_name);
    } else if (std::regex_match(line, sm, system_include_regex)) {
      CHECK(sm.size() == 2);
      file.system_includes.push_back(sm[1]);
    } else if (std::regex_match(line, sm, test_start_regex)) {
      CHECK(sm.size() == 2);
      CHECK(solver_name.empty());  // TODO FIXME no check
      solver_name = sm[1];
      break;
    } else {
      file.code_lines.push_back(line);
    }
  }

  if (is_header) {
    if (!solver_name.empty()) {
      file.problems.push_back({ParsingProblem::Error, -1, "SolverTest found in header"});
    }
    if (pragma_once_count == 0) {
      file.problems.push_back({ParsingProblem::Warning, -1, "no \"#pragma once\" found"});
    } else if (pragma_once_count > 1) {
      file.problems.push_back({ParsingProblem::Warning, -1, "several \"#pragma once\" found"});
    }
  } else {
    if (solver_name.empty()) {
      file.problems.push_back({ParsingProblem::Error, -1, "SolverTest not found in the main file"});
    } else {
      file.code_lines.push_back("");
      file.code_lines.push_back("int main() {");
      file.code_lines.push_back("  " + solver_name + " solver;");
      file.code_lines.push_back("  solver.run();");
      file.code_lines.push_back("}");
    }
    if (pragma_once_count > 0) {
      file.problems.push_back({ParsingProblem::Warning, -1, "\"#pragma once\" found in a source_file"});
    }
  }
  return file;
}
