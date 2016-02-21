#pragma once

#include "tools/compiler/file_parser.h"


struct CompilerOptions {
    ParserOptions parser_options;
    std::string include_path;
};

std::string Compile(const std::string& main_file, CompilerOptions& options);
