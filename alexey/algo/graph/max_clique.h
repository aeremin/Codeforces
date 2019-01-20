#pragma once
#include <cassert>
#include <cstdint>

#include "graph/graph.h"
#include "iter/range.h"

inline int MaxBit(uint64_t mask) {
    assert(mask > 0);
    for (int i = 63; i >= 0; --i)
        if ((uint64_t(1) << i) & mask)
            return i;
    assert(false);
}

// Clique size + mask
using CliqueInfo = std::pair<int, uint64_t>;

inline CliqueInfo MaximumCliqueInternal(const UndirectedGraph<>& g, std::vector<CliqueInfo>& cache,
                                        const uint64_t mask) {
    if (mask == 0)
        return {0, 0};
    if (mask < cache.size() && cache[mask].first >= 0)
        return cache[mask];
    int max_bit = MaxBit(mask);
    uint64_t limited_mask = 0;
    for (auto [neighbour, unused] : g.out_nbrs(max_bit)) limited_mask += (uint64_t(1) << neighbour) & mask;
    const auto result_with_vertice_used = MaximumCliqueInternal(g, cache, limited_mask);
    const auto res =
        std::max(MaximumCliqueInternal(g, cache, mask - (uint64_t(1) << max_bit)),
                 {1 + result_with_vertice_used.first, result_with_vertice_used.second + (uint64_t(1) << max_bit)});
    if (mask < cache.size())
        cache[mask] = res;
    return res;
}

// Returns vertices of (some) maximum (i.e. ordering by size, not by inclusion) clique in the graph.
// Complexity is O(2^(n/2)), memory used is O(2^(n/2)), where n is the number of graph vertices.
// So reasonable limit for n is 40 (maybe 50).
// Hard limit is 63 due to implementation specifics.
inline std::vector<int> MaximumClique(const UndirectedGraph<>& g) {
    assert(g.num_vertices() < 64);
    std::vector<CliqueInfo> cache(uint64_t(1) << (g.num_vertices() / 2), {-1, 0});
    uint64_t full_mask = (uint64_t(1) << g.num_vertices()) - 1;
    const auto internal_result = MaximumCliqueInternal(g, cache, full_mask);
    std::vector<int> result;
    for (int i : range(g.num_vertices())) {
        if ((uint64_t(1) << i) & internal_result.second) {
            result.push_back(i);
        }
    }
    return result;
}