#pragma once

#include "util/check.h"


template<typename VectorT>
const typename VectorT::value_type& at(const VectorT& vec, size_t index) {
  CHECK_DEFAULT(index < vec.size());
  return vec[index];
}
template<typename VectorT>
typename VectorT::value_type& at(VectorT& vec, size_t index) {
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
