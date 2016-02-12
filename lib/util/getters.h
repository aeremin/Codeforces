#pragma once

#include "util/check.h"


template<typename VectorT>
const typename VectorT::value_type& vec_at(const VectorT& vec, size_t index) {
  CHECK_DEFAULT(index < vec.size());
  return vec[index];
}
template<typename VectorT>
typename VectorT::value_type& vec_at(VectorT& vec, size_t index) {
  CHECK_DEBUG(index < vec.size());
  return vec[index];
}

template<typename MapT>
const typename MapT::mapped_type& map_at(const MapT& map, const typename MapT::key_type& key) {
  auto it = map.find(key);
  CHECK_DEBUG(it != map.end());
  return it->second;
}
template<typename MapT>
typename MapT::mapped_type& map_at(MapT& map, const typename MapT::key_type& key) {
  auto it = map.find(key);
  CHECK_DEBUG(it != map.end());
  return it->second;
}
