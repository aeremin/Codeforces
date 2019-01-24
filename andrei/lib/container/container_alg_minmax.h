#pragma once

#include "container/container_alg.h"


template <typename Sequence>
c_alg_internal::ContainerIter<Sequence> c_min_element(Sequence& sequence) {
    return std::min_element(c_alg_internal::c_begin(sequence), c_alg_internal::c_end(sequence));
}

template <typename Sequence, typename Compare>
c_alg_internal::ContainerIter<Sequence> c_min_element(Sequence& sequence, Compare&& comp) {
    return std::min_element(c_alg_internal::c_begin(sequence), c_alg_internal::c_end(sequence),
                            std::forward<Compare>(comp));
}

template <typename Sequence>
c_alg_internal::ContainerIter<Sequence> c_max_element(Sequence& sequence) {
    return std::max_element(c_alg_internal::c_begin(sequence), c_alg_internal::c_end(sequence));
}

template <typename Sequence, typename Compare>
c_alg_internal::ContainerIter<Sequence> c_max_element(Sequence& sequence, Compare&& comp) {
    return std::max_element(c_alg_internal::c_begin(sequence), c_alg_internal::c_end(sequence),
                            std::forward<Compare>(comp));
}

template <typename C>
c_alg_internal::ContainerIterPairType<C, C> c_minmax_element(C& c) {
    return std::minmax_element(c_alg_internal::c_begin(c), c_alg_internal::c_end(c));
}

template <typename C, typename Compare>
c_alg_internal::ContainerIterPairType<C, C> c_minmax_element(C& c, Compare&& comp) {
    return std::minmax_element(c_alg_internal::c_begin(c), c_alg_internal::c_end(c), std::forward<Compare>(comp));
}
