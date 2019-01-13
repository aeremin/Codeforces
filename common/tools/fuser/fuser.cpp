#include "fuser.h"

#include <algorithm>
#include <locale>
#include <fstream>
#include <functional>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "graph/graph.h"
#include "container/indexer.h"
#include "graph/topological_sort_checked.h"

const std::string kIndent = "  ";
const std::string kIncludedFromPrefix = kIndent + "from ";


std::string Compile(const std::string& main_file, CompilerOptions& options) {
    Indexer<std::string> file_indexer;
    Indexer<std::string> file_indexer_normalized;
    std::vector<ParsedFile> files;
    std::set<std::string> system_includes;
    DirectedGraph<> include_graph(0);

    std::function<int(const std::string&, bool)> process_file =
            [&](const std::string& file_name, bool is_header) {
        auto it = file_indexer.insert(file_name);
        int file_index = it.first;
        if (!it.second)
            return file_index;    // already parsed
        std::string file_name_normalized = file_name;
        std::transform(file_name_normalized.begin(), file_name_normalized.end(), file_name_normalized.begin(), ::tolower);
        auto it_normalized = file_indexer_normalized.insert(file_name_normalized);
        if (!it_normalized.second)
            throw std::runtime_error("Include case mismatch: " + file_name_normalized);
        const auto& include_paths = is_header ? options.include_paths : std::vector<std::string>{"."};
        bool file_found = false;
        for (const auto& include_path : include_paths) {
            const std::string file_path = include_path + "/" + file_name;
            std::fstream input(file_path, std::ios_base::in);
            if (!input.fail()) {
                file_found = true;
                files.push_back(ParseFile(input, options.parser_options, is_header));
                break;
            }
        }
        if (!file_found) {
            std::cerr << "Error: cannot find file \"" << file_name << "\"\n";
            throw std::runtime_error("Fatal error parsing " + file_name);
        }
        const ParsedFile current_file = files.back();
        for (const ParsingProblem& problem : current_file.problems) {
            const std::string location = file_name + ((problem.line >= 0) ? ":" + std::to_string(problem.line) : "");
            switch (problem.severity) {
                case ParsingProblem::Warning:
                    std::cerr << "Warning in " << location << ": " << problem.message << "\n";
                    break;
                case ParsingProblem::Error:
                    std::cerr << "Error in " << location << ": " << problem.message << "\n";
                    throw std::runtime_error("Fatal error parsing " + file_name);
            }
        }
        system_includes.insert(current_file.system_includes.begin(),
                               current_file.system_includes.end());
        for (const std::string& dependency : current_file.local_includes) {
            try {
                int dependency_index = process_file(dependency, true);
                include_graph.expand_to_num_vertices(file_index + 1);
                include_graph.expand_to_num_vertices(dependency_index + 1);
                include_graph.add_directed_edge(file_index, dependency_index);
            } catch (const std::runtime_error& err) {
                throw std::runtime_error(std::string(err.what()) + "\n" + kIncludedFromPrefix + file_name);
            }
        }
        return file_index;
    };

    int main_file_index = process_file(main_file, false);
    const auto file_indices_sorted = topological_sort_reachable_checked(include_graph, {main_file_index});
    switch (file_indices_sorted.status()) {
        case TopologicalSortResult::Ok:
            break;
        case TopologicalSortResult::LoopDetected:
            int loop_start = *(file_indices_sorted.loop().end() - 1);
            std::string inclusion_sequence = kIndent + file_indexer.value(loop_start);
            for (auto it = file_indices_sorted.vertices().begin();
                    it != file_indices_sorted.vertices().end(); ++it) {
                const std::string loop_marker = (*it == loop_start) ? " (!)" : "";
                inclusion_sequence += "\n" + kIncludedFromPrefix + file_indexer.value(*it) + loop_marker;
            }
            throw std::runtime_error("Fatal error: inclusion loop detected:\n" + inclusion_sequence);
    }

    std::stringstream output;
    for (const std::string& s : system_includes)
        output << "#include <" << s << ">\n";
    output << "\n\n";
    for (int file_index : file_indices_sorted.vertices()) {
        output << "\n" << "// From " << file_indexer.value(file_index) << "\n\n";
        for (const std::string& l : files.at(file_index).code_lines)
            output << l << "\n";
        output << "\n";
    }
    return output.str();
}
