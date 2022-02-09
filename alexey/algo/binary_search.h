#pragma once

// Find first iter in [first, last) such that condition(*iter) is true,
// in assumption that from condition(*iter) == true follows that condition(*(iter + 1)) == true
// If there is no such iter, returns last
template <class RandomAccessIterator, class Condition>
RandomAccessIterator binarySearch(RandomAccessIterator first, RandomAccessIterator last, Condition condition) {
    if (last > first && condition(*first))
        return first;

    auto left = first;
    auto right = last;
    while (right - left > 1) {
        auto center = left + (right - left) / 2;
        if (condition(*center))
            right = center;
        else
            left = center;
    }
    return right;
}