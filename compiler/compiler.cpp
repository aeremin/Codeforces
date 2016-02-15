#include <cassert>

#include <functional>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include <boost/program_options.hpp>

#include "container/indexer.h"
#include "graph/topological_sort.h"

#include "file_parser.h"

namespace po = boost::program_options;

constexpr int kBadCommandLine = 1;
constexpr int kRuntimeError = 2;

const std::string kIndent = "  ";
const std::string kIncludedFromPrefix = kIndent + "from ";


int main(int argc, char* argv[]) {
  po::options_description opts("Allowed options");
  opts.add_options()
    ("help", "produce help message")
    ("strip-comments", "remove comments from the file")
    ("include-path", po::value<std::string>(), "include path")
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

  ParserOptions parser_options;
  parser_options.strip_comments = var_map.count("strip-comments");
  const std::string include_path = var_map.count("include-path") ? var_map["include-path"].as<std::string>() : "";
  const std::string input_file = var_map["input-file"].as<std::string>();

  Indexer<std::string> file_indexer;
  std::vector<ParsedFile> files;
  std::set<std::string> system_includes;
  DirectedGraph_AdjacencyList include_graph;

  std::function<int(const std::string&, bool)> process_file =
      [&](const std::string& file_name, bool is_header) {
    auto it = file_indexer.insert(file_name);
    int file_index = it.first;
    if (!it.second)
      return file_index;  // already parsed
    const std::string file_path = (is_header ? include_path + "/" : "") + file_name;
    files.push_back(parse_file(file_path, parser_options, is_header));
    const ParsedFile& current_file = files.back();
    for (const ParsingProblem& problem : current_file.problems) {
      const std::string location = file_name +
                                   ((problem.line >= 0) ? ":" + std::to_string(problem.line) : "");
      switch (problem.severity) {
        case ParsingProblem::Warning:
          std::cerr << "Warning in " << location << ": " << problem.message << "\n";
          break;
        case ParsingProblem::Error:
          std::cerr << "Error in " << location << ": " << problem.message << "\n";
          throw std::runtime_error("Fatal error parsing " + file_name);
          break;
      }
    }
    system_includes.insert(current_file.system_includes.begin(),
                           current_file.system_includes.end());
    for (const std::string& dependency : current_file.local_includes) {
      try {
        int dependency_index = process_file(dependency, true);
        include_graph.add_arc_with_vertices(file_index, dependency_index);
      } catch (const std::runtime_error& err) {
        throw std::runtime_error(std::string(err.what()) + "\n" + kIncludedFromPrefix + file_name);
      }
    }
    return file_index;
  };

  try {
    int main_file_index = process_file(input_file, false);
    const auto file_indices_sorted = topological_sort_reachable_checked(include_graph, {main_file_index});
    switch (file_indices_sorted.status()) {
      case TopologicalSortResult::Ok:
        break;
      case TopologicalSortResult::LoopDetected:
        GraphIndex loop_start = file_indices_sorted.loop().back();
        std::string inclusion_sequence = kIndent + file_indexer.value(loop_start);
        for (auto it = file_indices_sorted.vertices().begin();
                  it != file_indices_sorted.vertices().end(); ++it) {
          const std::string loop_marker = (*it == loop_start) ? " (!)" : "";
          inclusion_sequence += "\n" + kIncludedFromPrefix + file_indexer.value(*it) + loop_marker;
        }
        throw std::runtime_error("Fatal error: inclusion loop detected:\n" + inclusion_sequence);
    }

    for (const std::string& s : system_includes)
      std::cout << "#include <" << s << ">\n";
    std::cout << "\n\n";
    for (GraphIndex file_index : file_indices_sorted.vertices()) {
      std::cout << "\n" << "// From " << file_indexer.value(file_index) << "\n\n";
      for (const std::string& l : files.at(file_index).code_lines)
        std::cout << l << "\n";
      std::cout << "\n";
    }
  } catch (const std::exception& exception) {
    std::cerr << exception.what() << std::endl;
    return kRuntimeError;
  }
}
