#pragma once

#include "container/container_alg.h"


template <typename C, typename Pred>
bool c_all_of(const C& c, Pred&& pred) {
    return std::all_of(c_alg_internal::c_begin(c), c_alg_internal::c_end(c), std::forward<Pred>(pred));
}

template <typename C, typename Pred>
bool c_any_of(const C& c, Pred&& pred) {
    return std::any_of(c_alg_internal::c_begin(c), c_alg_internal::c_end(c), std::forward<Pred>(pred));
}

template <typename C, typename Pred>
bool c_none_of(const C& c, Pred&& pred) {
    return std::none_of(c_alg_internal::c_begin(c), c_alg_internal::c_end(c), std::forward<Pred>(pred));
}
