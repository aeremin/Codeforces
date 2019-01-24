#pragma once

#include "container/container_alg.h"


template <typename Sequence, typename T>
std::decay_t<T> c_accumulate(const Sequence& sequence, T&& init) {
    return std::accumulate(c_alg_internal::c_begin(sequence), c_alg_internal::c_end(sequence), std::forward<T>(init));
}

template <typename Sequence, typename T, typename BinaryOp>
std::decay_t<T> c_accumulate(const Sequence& sequence, T&& init, BinaryOp&& binary_op) {
    return std::accumulate(c_alg_internal::c_begin(sequence), c_alg_internal::c_end(sequence), std::forward<T>(init),
                           std::forward<BinaryOp>(binary_op));
}
