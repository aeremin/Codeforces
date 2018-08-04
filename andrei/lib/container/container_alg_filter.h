#pragma once

#include "container/container_alg.h"


template <typename C, typename T>
void c_remove_erase(C& c, T&& value) {
  c.erase(std::remove(c_alg_internal::c_begin(c),
                      c_alg_internal::c_end(c),
                      std::forward<T>(value)),
          c.end());
}

template <typename C, typename Pred>
void c_remove_erase_if(C& c, Pred&& pred) {
  c.erase(std::remove_if(c_alg_internal::c_begin(c),
                         c_alg_internal::c_end(c),
                         std::forward<Pred>(pred)),
          c.end());
}

template <typename C>
void c_unique_erase(C& c) {
  c.erase(std::unique(c_alg_internal::c_begin(c),
                      c_alg_internal::c_end(c)),
          c.end());
}

template <typename C, typename BinaryPredicate>
void c_unique_erase(C& c, BinaryPredicate&& pred) {
  c.erase(std::unique(c_alg_internal::c_begin(c),
                      c_alg_internal::c_end(c),
                      std::forward<BinaryPredicate>(pred)),
          c.end());
}
