#pragma once

#include "container/container_alg.h"


template <typename Sequence, typename T>
c_alg_internal::ContainerIter<Sequence> c_lower_bound(Sequence& sequence, T&& value) {
    return std::lower_bound(c_alg_internal::c_begin(sequence), c_alg_internal::c_end(sequence), std::forward<T>(value));
}

template <typename Sequence, typename T, typename Compare>
c_alg_internal::ContainerIter<Sequence> c_lower_bound(Sequence& sequence, T&& value, Compare&& comp) {
    return std::lower_bound(c_alg_internal::c_begin(sequence), c_alg_internal::c_end(sequence), std::forward<T>(value),
                            std::forward<Compare>(comp));
}

template <typename Sequence, typename T>
c_alg_internal::ContainerIter<Sequence> c_upper_bound(Sequence& sequence, T&& value) {
    return std::upper_bound(c_alg_internal::c_begin(sequence), c_alg_internal::c_end(sequence), std::forward<T>(value));
}

template <typename Sequence, typename T, typename Compare>
c_alg_internal::ContainerIter<Sequence> c_upper_bound(Sequence& sequence, T&& value, Compare&& comp) {
    return std::upper_bound(c_alg_internal::c_begin(sequence), c_alg_internal::c_end(sequence), std::forward<T>(value),
                            std::forward<Compare>(comp));
}

template <typename Sequence, typename T>
c_alg_internal::ContainerIterPairType<Sequence, Sequence> c_equal_range(Sequence& sequence, T&& value) {
    return std::equal_range(c_alg_internal::c_begin(sequence), c_alg_internal::c_end(sequence), std::forward<T>(value));
}

template <typename Sequence, typename T, typename Compare>
c_alg_internal::ContainerIterPairType<Sequence, Sequence> c_equal_range(Sequence& sequence, T&& value, Compare&& comp) {
    return std::equal_range(c_alg_internal::c_begin(sequence), c_alg_internal::c_end(sequence), std::forward<T>(value),
                            std::forward<Compare>(comp));
}

template <typename Sequence, typename T>
bool c_binary_search(Sequence&& sequence, T&& value) {
    return std::binary_search(c_alg_internal::c_begin(sequence), c_alg_internal::c_end(sequence),
                              std::forward<T>(value));
}

template <typename Sequence, typename T, typename Compare>
bool c_binary_search(Sequence&& sequence, T&& value, Compare&& comp) {
    return std::binary_search(c_alg_internal::c_begin(sequence), c_alg_internal::c_end(sequence),
                              std::forward<T>(value), std::forward<Compare>(comp));
}
