#pragma once
#include <algorithm>
#include <utility>

template <class Iterator>
size_t lenOfMaximalIncreasingSubsequence(Iterator first, Iterator last) {
    std::vector<typename Iterator::value_type> lastsSubsequenceElts;
    for (auto it = first; it != last; ++it) {
        auto relaxIter = std::upper_bound(begin(lastsSubsequenceElts), end(lastsSubsequenceElts), *it);
        if (relaxIter == end(lastsSubsequenceElts))
            lastsSubsequenceElts.push_back(*it);
        else
            *relaxIter = *it;
    }
    return lastsSubsequenceElts.size();
}

template <class Iterator>
size_t lenOfMaximalIncreasingSubsegment(Iterator first, Iterator last) {
    if (first == last) {
        return 0;
    }
    auto result = 0;
    auto currSegmentStart = first;
    for (auto it = first + 1; it != last; ++it) {
        if (*it < *(it - 1)) {
            result = std::max<int>(result, std::distance(currSegmentStart, it));
            currSegmentStart = it;
        }
    }

    result = std::max<int>(result, std::distance(currSegmentStart, last));

    return result;
}