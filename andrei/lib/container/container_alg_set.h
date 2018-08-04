#pragma once

#include "container/container_alg.h"


template <typename C1, typename C2, typename OutputIterator>
OutputIterator c_set_union(const C1& c1, const C2& c2, OutputIterator output) {
  return std::set_union(c_alg_internal::c_begin(c1),
                        c_alg_internal::c_end(c1),
                        c_alg_internal::c_begin(c2),
                        c_alg_internal::c_end(c2), output);
}

template <typename C1, typename C2, typename OutputIterator, typename Compare>
OutputIterator c_set_union(const C1& c1, const C2& c2, OutputIterator output,
                           Compare&& comp) {
  return std::set_union(c_alg_internal::c_begin(c1),
                        c_alg_internal::c_end(c1),
                        c_alg_internal::c_begin(c2),
                        c_alg_internal::c_end(c2), output,
                        std::forward<Compare>(comp));
}

template <typename C1, typename C2, typename OutputIterator>
OutputIterator c_set_intersection(const C1& c1, const C2& c2,
                                  OutputIterator output) {
  return std::set_intersection(c_alg_internal::c_begin(c1),
                               c_alg_internal::c_end(c1),
                               c_alg_internal::c_begin(c2),
                               c_alg_internal::c_end(c2), output);
}

template <typename C1, typename C2, typename OutputIterator, typename Compare>
OutputIterator c_set_intersection(const C1& c1, const C2& c2,
                                  OutputIterator output, Compare&& comp) {
  return std::set_intersection(c_alg_internal::c_begin(c1),
                               c_alg_internal::c_end(c1),
                               c_alg_internal::c_begin(c2),
                               c_alg_internal::c_end(c2), output,
                               std::forward<Compare>(comp));
}

template <typename C1, typename C2, typename OutputIterator>
OutputIterator c_set_difference(const C1& c1, const C2& c2,
                                OutputIterator output) {
  return std::set_difference(c_alg_internal::c_begin(c1),
                             c_alg_internal::c_end(c1),
                             c_alg_internal::c_begin(c2),
                             c_alg_internal::c_end(c2), output);
}

template <typename C1, typename C2, typename OutputIterator, typename Compare>
OutputIterator c_set_difference(const C1& c1, const C2& c2,
                                OutputIterator output, Compare&& comp) {
  return std::set_difference(c_alg_internal::c_begin(c1),
                             c_alg_internal::c_end(c1),
                             c_alg_internal::c_begin(c2),
                             c_alg_internal::c_end(c2), output,
                             std::forward<Compare>(comp));
}

template <typename C1, typename C2, typename OutputIterator>
OutputIterator c_set_symmetric_difference(const C1& c1, const C2& c2,
                                          OutputIterator output) {
  return std::set_symmetric_difference(
      c_alg_internal::c_begin(c1),
      c_alg_internal::c_end(c1),
      c_alg_internal::c_begin(c2),
      c_alg_internal::c_end(c2), output);
}

template <typename C1, typename C2, typename OutputIterator, typename Compare>
OutputIterator c_set_symmetric_difference(const C1& c1, const C2& c2,
                                          OutputIterator output,
                                          Compare&& comp) {
  return std::set_symmetric_difference(
      c_alg_internal::c_begin(c1),
      c_alg_internal::c_end(c1),
      c_alg_internal::c_begin(c2),
      c_alg_internal::c_end(c2), output,
      std::forward<Compare>(comp));
}
