#pragma once

#include <iterator>
#include <utility>

using std::distance;
using std::swap;

// "Private" function
namespace {
template <class RandomAccessIterator>
RandomAccessIterator partition(RandomAccessIterator first, RandomAccessIterator last) {
    auto partitioningEltIter = first + rand() % (last - first);
    swap(*partitioningEltIter, *(last - 1));
    partitioningEltIter = last - 1;

    auto lastLowIter = first;
    int numSameElts = 0;
    for (auto iter = first; iter != last - 1; ++iter) {
        if (*iter < *partitioningEltIter || (*iter == *partitioningEltIter && ++numSameElts % 2 == 0)) {
            swap(*iter, *lastLowIter);
            ++lastLowIter;
        }
    }
    swap(*partitioningEltIter, *lastLowIter);
    return lastLowIter;
}
}  // namespace


template <class RandomAccessIterator>
void quickSort(RandomAccessIterator first, RandomAccessIterator last) {
    if (distance(first, last) <= 1)
        return;

    auto partitionEltIter = partition(first, last);
    quickSort(first, partitionEltIter);
    quickSort(partitionEltIter + 1, last);
}
