#pragma once

#include "container/container_alg.h"


template <typename C1, typename C2>
bool c_is_permutation(const C1& c1, const C2& c2) {
  using std::begin;
  using std::end;
  return c1.size() == c2.size() &&
         std::is_permutation(begin(c1), end(c1), begin(c2));
}

template <typename C1, typename C2, typename BinaryPredicate>
bool c_is_permutation(const C1& c1, const C2& c2, BinaryPredicate&& pred) {
  using std::begin;
  using std::end;
  return c1.size() == c2.size() &&
         std::is_permutation(begin(c1), end(c1), begin(c2),
                             std::forward<BinaryPredicate>(pred));
}

template <typename C>
bool c_next_permutation(C& c) {
  return std::next_permutation(c_alg_internal::c_begin(c),
                               c_alg_internal::c_end(c));
}

template <typename C, typename Compare>
bool c_next_permutation(C& c, Compare&& comp) {
  return std::next_permutation(c_alg_internal::c_begin(c),
                               c_alg_internal::c_end(c),
                               std::forward<Compare>(comp));
}

template <typename C>
bool c_prev_permutation(C& c) {
  return std::prev_permutation(c_alg_internal::c_begin(c),
                               c_alg_internal::c_end(c));
}

template <typename C, typename Compare>
bool c_prev_permutation(C& c, Compare&& comp) {
  return std::prev_permutation(c_alg_internal::c_begin(c),
                               c_alg_internal::c_end(c),
                               std::forward<Compare>(comp));
}
