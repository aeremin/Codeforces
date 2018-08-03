// Indexer allows to:
//   - assign numeric indices to values of any type, and
//   - map values to indices and vice versa.

#pragma once

#include <vector>
#include <unordered_map>

#include "util/getters.h"


template<typename ValueT>
class Indexer {
public:
  int size() const {
    return int(index_to_value_.size());
  }

  std::pair<int, bool> insert(ValueT value__) {
    int new_index = int(index_to_value_.size());
    auto res = value_to_index_.insert({value__, new_index});
    if (!res.second)
      return {res.first->second, false};
    index_to_value_.push_back(std::move(value__));
    return {new_index, true};
  }

  int insert_new(const ValueT& value__) {
    auto result = insert(value__);
    CHECK_DEFAULT(result.second);
    return result.first;
  }

  bool has_value(const ValueT& value__) const {
    return value_to_index_.count(value__) > 0;
  }

  int index(const ValueT& value__) const {
    return at(value_to_index_, value__);
  }

  const ValueT& value(int index__) const {
    return at(index_to_value_, index__);
  }

private:
  std::vector<ValueT> index_to_value_;
  std::unordered_map<ValueT, int> value_to_index_;
};
