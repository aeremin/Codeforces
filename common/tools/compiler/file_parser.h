#pragma once

#include <string>
#include <vector>


struct ParserOptions {
    bool strip_comments = false;
};

struct ParsingProblem {
    enum Severity {
        Warning,
        Error,
    };
    Severity severity;
    int line;
    std::string message;
};

struct ParsedFile {
    std::vector<std::string> local_includes;
    std::vector<std::string> system_includes;
    std::vector<std::string> code_lines;
    std::vector<ParsingProblem> problems;
};

ParsedFile ParseFile(const std::string& path, const ParserOptions& options, bool is_header);
