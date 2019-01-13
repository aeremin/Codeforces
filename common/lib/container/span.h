// Simplified version of std::span from C++20.

#pragma once

#include <iterator>
#include <type_traits>

#include "util/check.h"


template<typename T>
class span {
public:
  using element_type = T;
  using value_type = std::remove_cv_t<T>;
  using index_type = std::ptrdiff_t;
  using difference_type = std::ptrdiff_t;
  using pointer = T*;
  using reference = T&;
  using iterator = T*;
  using const_iterator = const T*;

  span() {}
  span(pointer ptr, index_type count) : begin_(ptr), end_(ptr + count) {}
  span(pointer firstElem, pointer lastElem) : begin_(firstElem), end_(lastElem) {}
  template <class Container>
  span(Container& cont) : begin_(&*std::begin(cont)), end_(&*std::end(cont)) {}
  template <class Container>
  span(const Container& cont) : begin_(&*std::begin(cont)), end_(&*std::end(cont)) {}

  reference operator[](index_type index) const { *(begin_ + index); }

  iterator begin() const        { return begin_; }
  iterator end() const          { return end_; }

  bool empty() const            { return end_ == begin_; }
  index_type size() const       { return end_ - begin_; }

  span first(index_type count) const                      { return {begin_, begin_ + count}; }
  span last(index_type count) const                       { return {end_ - count, end_}; }
  span subspan(index_type offset, index_type count) const { return {begin_ + offset, count}; }

private:
  pointer begin_ = nullptr;
  pointer end_ = nullptr;
};
