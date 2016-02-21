// Container view.
//
// Mimics STL container behavior, except that copying is cheap and only
// creates a new view.
//
// View is defined by a pair of iterators. View is invalidated when the
// underlying container is destroyed or when `begin()` or `end()` iterators
// are otherwise invalidated.
//
// Some operation may not be available for all iterator types.
// All available operation are O(1), std::advance and std::distance are
// deliberately not used.
//
// Creation:
//
// * make_view(begin, end)
//   creates view for [begin, end)
//
// * make_view(container)
//   creates view of the whole container, equivalent to
//   `make_view(begin(container), end(container))`

#pragma once

#include <iterator>
#include <stdexcept>

#include "util/check.h"


template<typename IteratorT>
class ContainterView {
private:
  using Value = decltype(*IteratorT());

public:
  ContainterView(IteratorT begin__, IteratorT end__) : begin_(begin__), end_(end__) {}

  const Value& operator[](size_t index) const   { return *(begin_ + index); }
  Value& operator[](size_t index)               { return *(begin_ + index); }
  const Value& at(size_t index) const           { check_index(index);  return *(begin_ + index); }
  Value& at(size_t index)                       { check_index(index);  return *(begin_ + index); }

  const Value& front() const    { return *begin_; }
  Value& front()                { return *begin_; }
  const Value& back() const     { return *std::prev(end_); }
  Value& back()                 { return *std::prev(end_); }

  IteratorT begin() const       { return begin_; }
  IteratorT end() const         { return end_; }

  bool empty() const            { return end_ == begin_; }
  // size() could have used std::distance, but I actually don't want it to compile when not O(1).
  size_t size() const           { return end_ - begin_; }

private:
  void check_index(size_t index) {
    CHECK_DEBUG(index < size());
  }

  IteratorT begin_ = {};
  IteratorT end_ = {};
};


template<typename IteratorT>
ContainterView<IteratorT> make_view(IteratorT begin, IteratorT end) {
  return {begin, end};
}

template<typename ContainerT>
auto make_view(ContainerT container) -> ContainterView<decltype(std::begin(container))> {
  return {std::begin(container), std::end(container)};
}
