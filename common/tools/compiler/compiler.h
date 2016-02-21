#pragma once

#include "tools/compiler/file_parser.h"


struct CompilerOptions {
    ParserOptions parser_options;
    std::vector<std::string> include_paths;
};

std::string Compile(const std::string& main_file, CompilerOptions& options);
