#pragma once

#include <iterator>
#include <utility>
#include <vector>

using std::copy;
using std::distance;

template <class RandomAccessIterator>
void mergeSort(RandomAccessIterator first, RandomAccessIterator last) {
    size_t dist = distance(first, last);
    if (dist <= 1)
        return;

    auto center = first + dist / 2;
    mergeSort(first, center);
    mergeSort(center, last);

    // We need to "backup" left part as it will be rewritten
    std::vector<typename RandomAccessIterator::value_type> backup(dist / 2);
    copy(first, center, begin(backup));

    auto leftPartIter = begin(backup);
    auto leftPartEnd = end(backup);
    auto rightPartIter = center;
    auto rightPartEnd = last;

    for (auto resultIter = first; resultIter != last; ++resultIter) {
        if (leftPartIter != leftPartEnd && (rightPartIter == rightPartEnd || *leftPartIter < *rightPartIter)) {
            *resultIter = *leftPartIter;
            ++leftPartIter;
        } else {
            *resultIter = *rightPartIter;
            ++rightPartIter;
        }
    }
}
