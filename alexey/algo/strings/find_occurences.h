#pragma once
#include <numeric>
#include <vector>

#include "algo/strings/knutt_morris_pratt.h"
#include "iter/range.h"

// Returns vector of indices i such that text[i...i + pattern.size() - 1] == pattern.
// Time complexity is O(text.size() + pattern.size()).
template <class Container>
std::vector<size_t> FindOccurences(const Container& text, Container pattern) {
    auto patternSize = pattern.size();
    if (patternSize == 0) {
        std::vector<size_t> result(text.size());
        std::iota(begin(result), end(result), 0);
        return result;
    }

    auto concatenated = std::move(pattern);
    concatenated.insert(end(concatenated), begin(text), end(text));
    auto pi = PrefixFunction(concatenated);
    std::vector<size_t> result;
    for (auto i : range(patternSize - 1, text.size()))
        if (pi[i + patternSize] >= patternSize)
            result.push_back(i - patternSize + 1);
    return result;
}