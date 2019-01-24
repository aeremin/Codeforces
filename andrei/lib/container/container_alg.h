// Inspired by absl/algorithm/container.h

#pragma once

#include <algorithm>
#include <numeric>
#include <type_traits>


namespace c_alg_internal {

using std::begin;
using std::end;

template <typename C>
using ContainerIter = decltype(begin(std::declval<C&>()));

template <typename C1, typename C2>
using ContainerIterPairType = decltype(std::make_pair(ContainerIter<C1>(), ContainerIter<C2>()));

template <typename C>
using ContainerDifferenceType =
    decltype(std::distance(std::declval<ContainerIter<C>>(), std::declval<ContainerIter<C>>()));

template <typename C>
ContainerIter<C> c_begin(C& c) {
    return begin(c);
}

template <typename C>
ContainerIter<C> c_end(C& c) {
    return end(c);
}

}  // namespace c_alg_internal


template <typename C, typename Function>
std::decay_t<Function> c_for_each(C&& c, Function&& f) {
    return std::for_each(c_alg_internal::c_begin(c), c_alg_internal::c_end(c), std::forward<Function>(f));
}

template <typename C, typename T>
c_alg_internal::ContainerIter<C> c_find(C& c, T&& value) {
    return std::find(c_alg_internal::c_begin(c), c_alg_internal::c_end(c), std::forward<T>(value));
}

template <typename C, typename Pred>
c_alg_internal::ContainerIter<C> c_find_if(C& c, Pred&& pred) {
    return std::find_if(c_alg_internal::c_begin(c), c_alg_internal::c_end(c), std::forward<Pred>(pred));
}

template <typename C, typename T>
c_alg_internal::ContainerDifferenceType<const C> c_count(const C& c, T&& value) {
    return std::count(c_alg_internal::c_begin(c), c_alg_internal::c_end(c), std::forward<T>(value));
}

template <typename C, typename Pred>
c_alg_internal::ContainerDifferenceType<const C> c_count_if(const C& c, Pred&& pred) {
    return std::count_if(c_alg_internal::c_begin(c), c_alg_internal::c_end(c), std::forward<Pred>(pred));
}

template <typename Sequence>
void c_reverse(Sequence& sequence) {
    std::reverse(c_alg_internal::c_begin(sequence), c_alg_internal::c_end(sequence));
}


// Sorting functions

template <typename C>
void c_sort(C& c) {
    std::sort(c_alg_internal::c_begin(c), c_alg_internal::c_end(c));
}

template <typename C, typename Compare>
void c_sort(C& c, Compare&& comp) {
    std::sort(c_alg_internal::c_begin(c), c_alg_internal::c_end(c), std::forward<Compare>(comp));
}

template <typename C>
void c_stable_sort(C& c) {
    std::stable_sort(c_alg_internal::c_begin(c), c_alg_internal::c_end(c));
}

template <typename C, typename Compare>
void c_stable_sort(C& c, Compare&& comp) {
    std::stable_sort(c_alg_internal::c_begin(c), c_alg_internal::c_end(c), std::forward<Compare>(comp));
}
