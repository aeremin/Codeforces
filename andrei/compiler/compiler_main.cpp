#include <iostream>

#include <boost/program_options.hpp>

#include "tools/compiler/compiler.h"

namespace po = boost::program_options;

constexpr int kBadCommandLine = 1;
constexpr int kRuntimeError = 2;


int main(int argc, char* argv[]) {
    po::options_description opts("Allowed options");
    opts.add_options()
        ("help", "produce help message")
        ("strip-comments", "remove comments from the file")
        ("include-path", po::value<std::vector<std::string>>(), "include path")
        ("input-file", po::value<std::string>(), "input file")
    ;

    po::positional_options_description pos_opts;
    pos_opts.add("input-file", -1);

    po::variables_map var_map;
    po::store(po::command_line_parser(argc, argv).
                        options(opts).positional(pos_opts).run(), var_map);
    po::notify(var_map);

    if (var_map.count("help")) {
        std::cerr << opts;
        return kBadCommandLine;
    }

    if (var_map.count("input-file") != 1) {
        std::cerr << "Input file not specified!\n";
        std::cerr << opts;
        return kBadCommandLine;
    }

    CompilerOptions options;
    options.parser_options.strip_comments = var_map.count("strip-comments");
    options.include_paths = var_map["include-path"].as<std::vector<std::string>>();
    const std::string main_file = var_map["input-file"].as<std::string>();

    try {
        std::cout << Compile(main_file, options);
    } catch (const std::exception& exception) {
        std::cerr << exception.what() << std::endl;
        return kRuntimeError;
    }
}
