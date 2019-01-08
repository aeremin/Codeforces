// Convenience getter function for standard containers.
//
// * at(container, key)
//   Checks if 'key' is valid and returns `container[key]`.
//   Works similar to std::vector::at or std::map::at, but uses DEBUG_CHECK
//   instead of throwing exceptions.
//
// * value_or(container, key, default_value)
//   Returs `container[key]` if 'key' is valid or 'default_value' otherwise.
//   Works similar std::experimental::optional::value_or.

#pragma once

#include <optional>
#include "util/check.h"

template<typename VectorT>
typename VectorT::const_reference at(const VectorT& vec, size_t index) {
  CHECK_DEFAULT(index < vec.size());
  return vec[index];
}
template<typename VectorT>
typename VectorT::reference at(VectorT& vec, size_t index) {
  CHECK_DEBUG(index < vec.size());
  return vec[index];
}

template<typename MapT>
const typename MapT::mapped_type& at(const MapT& map, const typename MapT::key_type& key) {
  auto it = map.find(key);
  CHECK_DEBUG(it != map.end());
  return it->second;
}
template<typename MapT>
typename MapT::mapped_type& at(MapT& map, const typename MapT::key_type& key) {
  auto it = map.find(key);
  CHECK_DEBUG(it != map.end());
  return it->second;
}


template<typename VectorT>
typename VectorT::value_type value_or(const VectorT& vec, size_t index,
                                      const typename VectorT::value_type& default_value = {}) {
  return (index < vec.size()) ? vec[index] : default_value;
}

template<typename MapT>
typename MapT::mapped_type value_or(const MapT& map, const typename MapT::key_type& key,
                                    const typename MapT::mapped_type& default_value = {}) {
  return maybe_get(map, key).value_or(default_value);
}

template<typename MapT>
typename std::optional<typename MapT::mapped_type> maybe_get(const MapT& map, const typename MapT::key_type& key) {
  auto it = map.find(key);
  return (it != map.end()) ? it->second : std::optional<typename MapT::mapped_type>{};
}
