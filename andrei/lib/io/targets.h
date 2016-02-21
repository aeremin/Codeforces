#pragma once

#include <cstdio>
#include <string>

#include "util/compilers.h"


struct IOFileNames {
public:
    std::string input_file_name;
    std::string output_file_name;
};

IOFileNames input_txt_output_txt() {
    return {"input.txt", "output.txt"};
}
IOFileNames foo_in_foo_out(const std::string& file_name_base) {
    return {file_name_base + ".in", file_name_base + ".out"};
}
IOFileNames custom_file_names(const std::string& input_file_name, const std::string& output_file_name) {
    return {input_file_name, output_file_name};
}

void set_io_file_names(const IOFileNames& names) {
    FIX_UNUSED(names);
#ifndef LOCAL_PC
    freopen(names.input_file_name.c_str(), "r", stdin);
    freopen(names.output_file_name.c_str(), "w", stdout);
#endif
}
