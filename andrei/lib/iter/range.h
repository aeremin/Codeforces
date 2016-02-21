// Range-based style iteration helpers.
//
// * range(end)
//   Iterates over [0, end), e.g.:
//   ` for (auto i : range(5)) {
//   `   print(i);
//   ` }
//   prints "0 1 2 3 4"
//
// * range(begin, end)
//   Iterates over [begin, end), e.g.:
//   ` for (auto i : range(5, 10)) {
//   `   print(i);
//   ` }
//   prints "5 6 7 8 9"
//
// * FOR_TIMES(n)
//   Repeats loop body n times, e.g.:
//   ` print("We all live in a");
//   ` FOR_TIMES(3) {
//   `   print(" yellow submarine");
//   ` }

#pragma once


namespace internal {

template<typename ValueT>
class IterableRange {
public:
  class iterator {
  public:
    iterator(ValueT v__) : v_(v__) {}

    iterator& operator++() { ++v_; return *this; }

    bool operator==(iterator rhs) const { return v_ == rhs.v_; }
    bool operator!=(iterator rhs) const { return v_ != rhs.v_; }

    ValueT operator*() const  { return v_; }
    ValueT operator->() const { return v_; }

  private:
    ValueT v_ = {};
  };

  IterableRange(ValueT begin__, ValueT end__) : begin_value_(begin__), end_value_(end__) {}

  iterator begin() const { return {begin_value_}; }
  iterator end() const { return {end_value_}; }

private:
  ValueT begin_value_ = {};
  ValueT end_value_ = {};
};

}  // namespace internal


template<typename ValueT>
internal::IterableRange<ValueT> range(ValueT end) {
  return {{}, end};
}

template<typename ValueT>
internal::IterableRange<ValueT> range(ValueT begin, ValueT end) {
  return {begin, end};
}

#define FOR_TIMES(N_TIMES) \
  for (auto __counter = (N_TIMES); __counter > 0; --__counter)
