#pragma once
#include <utility>
#include <algorithm>

template<class Iterator>
size_t lenOfMaximalIncreasingSubsequence(Iterator first, Iterator last)
{
    std::vector<Iterator::value_type> lastsSubsequenceElts;
    for (auto it = first; it != last; ++it)
    {
        auto relaxIter = std::upper_bound(begin(lastsSubsequenceElts), end(lastsSubsequenceElts), *it);
        if (relaxIter == end(lastsSubsequenceElts))
            lastsSubsequenceElts.push_back(*it);
        else
            *relaxIter = *it;
    }
    return lastsSubsequenceElts.size();
}