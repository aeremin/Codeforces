// DO NOT USE: too big!
// TODO: split into separate files at a function granularity
// TODO: add `remove()`, `remove_if()` and `unique()` + erase

// Inspired by absl/algorithm/container.h

#pragma once

#include <algorithm>
#include <numeric>
#include <type_traits>


#if 0

namespace c_alg_internal {

// NOTE: it is important to defer to ADL lookup for building with C++ modules,
// especially for headers like <valarray> which are not visible from this file
// but specialize std::begin and std::end.
using std::begin;
using std::end;

template <typename C>
using ContainerIter = decltype(begin(std::declval<C&>()));

template <typename C1, typename C2>
using ContainerIterPairType =
    decltype(std::make_pair(ContainerIter<C1>(), ContainerIter<C2>()));

template <typename C>
using ContainerDifferenceType =
    decltype(std::distance(std::declval<ContainerIter<C>>(),
                           std::declval<ContainerIter<C>>()));

template <typename C>
ContainerIter<C> c_begin(C& c) { return begin(c); }

template <typename C>
ContainerIter<C> c_end(C& c) { return end(c); }

}  // namespace internal

// <algorithm> Non-modifying sequence operations

template <typename C, typename Pred>
bool c_all_of(const C& c, Pred&& pred) {
  return std::all_of(c_alg_internal::c_begin(c),
                     c_alg_internal::c_end(c),
                     std::forward<Pred>(pred));
}

template <typename C, typename Pred>
bool c_any_of(const C& c, Pred&& pred) {
  return std::any_of(c_alg_internal::c_begin(c),
                     c_alg_internal::c_end(c),
                     std::forward<Pred>(pred));
}

template <typename C, typename Pred>
bool c_none_of(const C& c, Pred&& pred) {
  return std::none_of(c_alg_internal::c_begin(c),
                      c_alg_internal::c_end(c),
                      std::forward<Pred>(pred));
}

template <typename C, typename Function>
std::decay_t<Function> c_for_each(C&& c, Function&& f) {
  return std::for_each(c_alg_internal::c_begin(c),
                       c_alg_internal::c_end(c),
                       std::forward<Function>(f));
}

template <typename C, typename T>
c_alg_internal::ContainerIter<C> c_find(C& c, T&& value) {
  return std::find(c_alg_internal::c_begin(c),
                   c_alg_internal::c_end(c),
                   std::forward<T>(value));
}

template <typename C, typename Pred>
c_alg_internal::ContainerIter<C> c_find_if(C& c, Pred&& pred) {
  return std::find_if(c_alg_internal::c_begin(c),
                      c_alg_internal::c_end(c),
                      std::forward<Pred>(pred));
}

template <typename C, typename Pred>
c_alg_internal::ContainerIter<C> c_find_if_not(C& c, Pred&& pred) {
  return std::find_if_not(c_alg_internal::c_begin(c),
                          c_alg_internal::c_end(c),
                          std::forward<Pred>(pred));
}

template <typename Sequence1, typename Sequence2>
c_alg_internal::ContainerIter<Sequence1> c_find_end(
    Sequence1& sequence, Sequence2& subsequence) {
  return std::find_end(c_alg_internal::c_begin(sequence),
                       c_alg_internal::c_end(sequence),
                       c_alg_internal::c_begin(subsequence),
                       c_alg_internal::c_end(subsequence));
}

template <typename Sequence1, typename Sequence2, typename BinaryPredicate>
c_alg_internal::ContainerIter<Sequence1> c_find_end(
    Sequence1& sequence, Sequence2& subsequence, BinaryPredicate&& pred) {
  return std::find_end(c_alg_internal::c_begin(sequence),
                       c_alg_internal::c_end(sequence),
                       c_alg_internal::c_begin(subsequence),
                       c_alg_internal::c_end(subsequence),
                       std::forward<BinaryPredicate>(pred));
}

template <typename C1, typename C2>
c_alg_internal::ContainerIter<C1> c_find_first_of(C1& container, C2& options) {
  return std::find_first_of(c_alg_internal::c_begin(container),
                            c_alg_internal::c_end(container),
                            c_alg_internal::c_begin(options),
                            c_alg_internal::c_end(options));
}

template <typename C1, typename C2, typename BinaryPredicate>
c_alg_internal::ContainerIter<C1> c_find_first_of(
    C1& container, C2& options, BinaryPredicate&& pred) {
  return std::find_first_of(c_alg_internal::c_begin(container),
                            c_alg_internal::c_end(container),
                            c_alg_internal::c_begin(options),
                            c_alg_internal::c_end(options),
                            std::forward<BinaryPredicate>(pred));
}

template <typename Sequence>
c_alg_internal::ContainerIter<Sequence> c_adjacent_find(
    Sequence& sequence) {
  return std::adjacent_find(c_alg_internal::c_begin(sequence),
                            c_alg_internal::c_end(sequence));
}

template <typename Sequence, typename BinaryPredicate>
c_alg_internal::ContainerIter<Sequence> c_adjacent_find(
    Sequence& sequence, BinaryPredicate&& pred) {
  return std::adjacent_find(c_alg_internal::c_begin(sequence),
                            c_alg_internal::c_end(sequence),
                            std::forward<BinaryPredicate>(pred));
}

template <typename C, typename T>
c_alg_internal::ContainerDifferenceType<const C> c_count(
    const C& c, T&& value) {
  return std::count(c_alg_internal::c_begin(c),
                    c_alg_internal::c_end(c),
                    std::forward<T>(value));
}

template <typename C, typename Pred>
c_alg_internal::ContainerDifferenceType<const C> c_count_if(
    const C& c, Pred&& pred) {
  return std::count_if(c_alg_internal::c_begin(c),
                       c_alg_internal::c_end(c),
                       std::forward<Pred>(pred));
}

template <typename C1, typename C2>
c_alg_internal::ContainerIterPairType<C1, C2>
c_mismatch(C1& c1, C2& c2) {
  return std::mismatch(c_alg_internal::c_begin(c1),
                       c_alg_internal::c_end(c1),
                       c_alg_internal::c_begin(c2));
}

template <typename C1, typename C2, typename BinaryPredicate>
c_alg_internal::ContainerIterPairType<C1, C2>
c_mismatch(C1& c1, C2& c2, BinaryPredicate&& pred) {
  return std::mismatch(c_alg_internal::c_begin(c1),
                       c_alg_internal::c_end(c1),
                       c_alg_internal::c_begin(c2),
                       std::forward<BinaryPredicate>(pred));
}

// NOTE: Compared to std::equal(), also checks whether the container sizes are equal.
template <typename C1, typename C2>
bool c_equal(const C1& c1, const C2& c2) {
  return ((c1.size() == c2.size()) &&
          std::equal(c_alg_internal::c_begin(c1),
                     c_alg_internal::c_end(c1),
                     c_alg_internal::c_begin(c2)));
}

template <typename C1, typename C2, typename BinaryPredicate>
bool c_equal(const C1& c1, const C2& c2, BinaryPredicate&& pred) {
  return ((c1.size() == c2.size()) &&
          std::equal(c_alg_internal::c_begin(c1),
                     c_alg_internal::c_end(c1),
                     c_alg_internal::c_begin(c2),
                     std::forward<BinaryPredicate>(pred)));
}

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

template <typename Sequence1, typename Sequence2>
c_alg_internal::ContainerIter<Sequence1> c_search(
    Sequence1& sequence, Sequence2& subsequence) {
  return std::search(c_alg_internal::c_begin(sequence),
                     c_alg_internal::c_end(sequence),
                     c_alg_internal::c_begin(subsequence),
                     c_alg_internal::c_end(subsequence));
}

template <typename Sequence1, typename Sequence2, typename BinaryPredicate>
c_alg_internal::ContainerIter<Sequence1> c_search(
    Sequence1& sequence, Sequence2& subsequence, BinaryPredicate&& pred) {
  return std::search(c_alg_internal::c_begin(sequence),
                     c_alg_internal::c_end(sequence),
                     c_alg_internal::c_begin(subsequence),
                     c_alg_internal::c_end(subsequence),
                     std::forward<BinaryPredicate>(pred));
}

template <typename Sequence, typename Size, typename T>
c_alg_internal::ContainerIter<Sequence> c_search_n(
    Sequence& sequence, Size count, T&& value) {
  return std::search_n(c_alg_internal::c_begin(sequence),
                       c_alg_internal::c_end(sequence), count,
                       std::forward<T>(value));
}

template <typename Sequence, typename Size, typename T,
          typename BinaryPredicate>
c_alg_internal::ContainerIter<Sequence> c_search_n(
    Sequence& sequence, Size count, T&& value, BinaryPredicate&& pred) {
  return std::search_n(c_alg_internal::c_begin(sequence),
                       c_alg_internal::c_end(sequence), count,
                       std::forward<T>(value),
                       std::forward<BinaryPredicate>(pred));
}

// <algorithm> Modifying sequence operations

template <typename InputSequence, typename OutputIterator>
OutputIterator c_copy(const InputSequence& input, OutputIterator output) {
  return std::copy(c_alg_internal::c_begin(input),
                   c_alg_internal::c_end(input), output);
}

template <typename C, typename Size, typename OutputIterator>
OutputIterator c_copy_n(const C& input, Size n, OutputIterator output) {
  return std::copy_n(c_alg_internal::c_begin(input), n, output);
}

template <typename InputSequence, typename OutputIterator, typename Pred>
OutputIterator c_copy_if(const InputSequence& input, OutputIterator output,
                         Pred&& pred) {
  return std::copy_if(c_alg_internal::c_begin(input),
                      c_alg_internal::c_end(input), output,
                      std::forward<Pred>(pred));
}

template <typename C, typename BidirectionalIterator>
BidirectionalIterator c_copy_backward(const C& src,
                                      BidirectionalIterator dest) {
  return std::copy_backward(c_alg_internal::c_begin(src),
                            c_alg_internal::c_end(src), dest);
}

template <typename C, typename OutputIterator>
OutputIterator c_move(C& src, OutputIterator dest) {
  return std::move(c_alg_internal::c_begin(src),
                   c_alg_internal::c_end(src), dest);
}

template <typename C1, typename C2>
c_alg_internal::ContainerIter<C2> c_swap_ranges(C1& c1, C2& c2) {
  return std::swap_ranges(c_alg_internal::c_begin(c1),
                          c_alg_internal::c_end(c1),
                          c_alg_internal::c_begin(c2));
}

template <typename InputSequence, typename OutputIterator, typename UnaryOp>
OutputIterator c_transform(const InputSequence& input, OutputIterator output,
                           UnaryOp&& unary_op) {
  return std::transform(c_alg_internal::c_begin(input),
                        c_alg_internal::c_end(input), output,
                        std::forward<UnaryOp>(unary_op));
}

template <typename InputSequence1, typename InputSequence2,
          typename OutputIterator, typename BinaryOp>
OutputIterator c_transform(const InputSequence1& input1,
                           const InputSequence2& input2, OutputIterator output,
                           BinaryOp&& binary_op) {
  return std::transform(c_alg_internal::c_begin(input1),
                        c_alg_internal::c_end(input1),
                        c_alg_internal::c_begin(input2), output,
                        std::forward<BinaryOp>(binary_op));
}

template <typename Sequence, typename T>
void c_replace(Sequence& sequence, const T& old_value, const T& new_value) {
  std::replace(c_alg_internal::c_begin(sequence),
               c_alg_internal::c_end(sequence), old_value,
               new_value);
}

template <typename C, typename Pred, typename T>
void c_replace_if(C& c, Pred&& pred, T&& new_value) {
  std::replace_if(c_alg_internal::c_begin(c),
                  c_alg_internal::c_end(c),
                  std::forward<Pred>(pred), std::forward<T>(new_value));
}

template <typename C, typename OutputIterator, typename T>
OutputIterator c_replace_copy(const C& c, OutputIterator result, T&& old_value,
                              T&& new_value) {
  return std::replace_copy(c_alg_internal::c_begin(c),
                           c_alg_internal::c_end(c), result,
                           std::forward<T>(old_value),
                           std::forward<T>(new_value));
}

template <typename C, typename OutputIterator, typename Pred, typename T>
OutputIterator c_replace_copy_if(const C& c, OutputIterator result, Pred&& pred,
                                 T&& new_value) {
  return std::replace_copy_if(c_alg_internal::c_begin(c),
                              c_alg_internal::c_end(c), result,
                              std::forward<Pred>(pred),
                              std::forward<T>(new_value));
}

template <typename C, typename T>
void c_fill(C& c, T&& value) {
  std::fill(c_alg_internal::c_begin(c),
            c_alg_internal::c_end(c), std::forward<T>(value));
}

template <typename C, typename Size, typename T>
void c_fill_n(C& c, Size n, T&& value) {
  std::fill_n(c_alg_internal::c_begin(c), n,
              std::forward<T>(value));
}

template <typename C, typename Generator>
void c_generate(C& c, Generator&& gen) {
  std::generate(c_alg_internal::c_begin(c),
                c_alg_internal::c_end(c),
                std::forward<Generator>(gen));
}

template <typename C, typename Size, typename Generator>
c_alg_internal::ContainerIter<C> c_generate_n(C& c, Size n, Generator&& gen) {
  return std::generate_n(c_alg_internal::c_begin(c), n,
                         std::forward<Generator>(gen));
}

template <typename C, typename OutputIterator, typename T>
OutputIterator c_remove_copy(const C& c, OutputIterator result, T&& value) {
  return std::remove_copy(c_alg_internal::c_begin(c),
                          c_alg_internal::c_end(c), result,
                          std::forward<T>(value));
}

template <typename C, typename OutputIterator, typename Pred>
OutputIterator c_remove_copy_if(const C& c, OutputIterator result,
                                Pred&& pred) {
  return std::remove_copy_if(c_alg_internal::c_begin(c),
                             c_alg_internal::c_end(c), result,
                             std::forward<Pred>(pred));
}

template <typename C, typename OutputIterator>
OutputIterator c_unique_copy(const C& c, OutputIterator result) {
  return std::unique_copy(c_alg_internal::c_begin(c),
                          c_alg_internal::c_end(c), result);
}

template <typename C, typename OutputIterator, typename BinaryPredicate>
OutputIterator c_unique_copy(const C& c, OutputIterator result,
                             BinaryPredicate&& pred) {
  return std::unique_copy(c_alg_internal::c_begin(c),
                          c_alg_internal::c_end(c), result,
                          std::forward<BinaryPredicate>(pred));
}

template <typename Sequence>
void c_reverse(Sequence& sequence) {
  std::reverse(c_alg_internal::c_begin(sequence),
               c_alg_internal::c_end(sequence));
}

template <typename C, typename OutputIterator>
OutputIterator c_reverse_copy(const C& sequence, OutputIterator result) {
  return std::reverse_copy(c_alg_internal::c_begin(sequence),
                           c_alg_internal::c_end(sequence),
                           result);
}

template <typename C,
          typename Iterator = c_alg_internal::ContainerIter<C>>
Iterator c_rotate(C& sequence, Iterator middle) {
  return std::rotate(c_alg_internal::c_begin(sequence), middle,
                     c_alg_internal::c_end(sequence));
}

template <typename C, typename OutputIterator>
OutputIterator c_rotate_copy(
    const C& sequence,
    c_alg_internal::ContainerIter<const C> middle,
    OutputIterator result) {
  return std::rotate_copy(c_alg_internal::c_begin(sequence),
                          middle, c_alg_internal::c_end(sequence),
                          result);
}

template <typename RandomAccessContainer, typename UniformRandomBitGenerator>
void c_shuffle(RandomAccessContainer& c, UniformRandomBitGenerator&& gen) {
  std::shuffle(c_alg_internal::c_begin(c),
               c_alg_internal::c_end(c),
               std::forward<UniformRandomBitGenerator>(gen));
}

// <algorithm> Partition functions

template <typename C, typename Pred>
bool c_is_partitioned(const C& c, Pred&& pred) {
  return std::is_partitioned(c_alg_internal::c_begin(c),
                             c_alg_internal::c_end(c),
                             std::forward<Pred>(pred));
}

template <typename C, typename Pred>
c_alg_internal::ContainerIter<C> c_partition(C& c, Pred&& pred) {
  return std::partition(c_alg_internal::c_begin(c),
                        c_alg_internal::c_end(c),
                        std::forward<Pred>(pred));
}

template <typename C, typename Pred>
c_alg_internal::ContainerIter<C> c_stable_partition(C& c, Pred&& pred) {
  return std::stable_partition(c_alg_internal::c_begin(c),
                               c_alg_internal::c_end(c),
                               std::forward<Pred>(pred));
}

template <typename C, typename OutputIterator1, typename OutputIterator2,
          typename Pred>
std::pair<OutputIterator1, OutputIterator2> c_partition_copy(
    const C& c, OutputIterator1 out_true, OutputIterator2 out_false,
    Pred&& pred) {
  return std::partition_copy(c_alg_internal::c_begin(c),
                             c_alg_internal::c_end(c), out_true,
                             out_false, std::forward<Pred>(pred));
}

template <typename C, typename Pred>
c_alg_internal::ContainerIter<C> c_partition_point(C& c, Pred&& pred) {
  return std::partition_point(c_alg_internal::c_begin(c),
                              c_alg_internal::c_end(c),
                              std::forward<Pred>(pred));
}

// <algorithm> Sorting functions

template <typename C>
void c_sort(C& c) {
  std::sort(c_alg_internal::c_begin(c),
            c_alg_internal::c_end(c));
}

template <typename C, typename Compare>
void c_sort(C& c, Compare&& comp) {
  std::sort(c_alg_internal::c_begin(c),
            c_alg_internal::c_end(c),
            std::forward<Compare>(comp));
}

template <typename C>
void c_stable_sort(C& c) {
  std::stable_sort(c_alg_internal::c_begin(c),
                   c_alg_internal::c_end(c));
}

template <typename C, typename Compare>
void c_stable_sort(C& c, Compare&& comp) {
  std::stable_sort(c_alg_internal::c_begin(c),
                   c_alg_internal::c_end(c),
                   std::forward<Compare>(comp));
}

template <typename C>
bool c_is_sorted(const C& c) {
  return std::is_sorted(c_alg_internal::c_begin(c),
                        c_alg_internal::c_end(c));
}

template <typename C, typename Compare>
bool c_is_sorted(const C& c, Compare&& comp) {
  return std::is_sorted(c_alg_internal::c_begin(c),
                        c_alg_internal::c_end(c),
                        std::forward<Compare>(comp));
}

template <typename RandomAccessContainer>
void c_partial_sort(
    RandomAccessContainer& sequence,
    c_alg_internal::ContainerIter<RandomAccessContainer> middle) {
  std::partial_sort(c_alg_internal::c_begin(sequence), middle,
                    c_alg_internal::c_end(sequence));
}

template <typename RandomAccessContainer, typename Compare>
void c_partial_sort(
    RandomAccessContainer& sequence,
    c_alg_internal::ContainerIter<RandomAccessContainer> middle,
    Compare&& comp) {
  std::partial_sort(c_alg_internal::c_begin(sequence), middle,
                    c_alg_internal::c_end(sequence),
                    std::forward<Compare>(comp));
}

template <typename C, typename RandomAccessContainer>
c_alg_internal::ContainerIter<RandomAccessContainer>
c_partial_sort_copy(const C& sequence, RandomAccessContainer& result) {
  return std::partial_sort_copy(c_alg_internal::c_begin(sequence),
                                c_alg_internal::c_end(sequence),
                                c_alg_internal::c_begin(result),
                                c_alg_internal::c_end(result));
}

template <typename C, typename RandomAccessContainer, typename Compare>
c_alg_internal::ContainerIter<RandomAccessContainer>
c_partial_sort_copy(const C& sequence, RandomAccessContainer& result,
                    Compare&& comp) {
  return std::partial_sort_copy(c_alg_internal::c_begin(sequence),
                                c_alg_internal::c_end(sequence),
                                c_alg_internal::c_begin(result),
                                c_alg_internal::c_end(result),
                                std::forward<Compare>(comp));
}

template <typename C>
c_alg_internal::ContainerIter<C> c_is_sorted_until(C& c) {
  return std::is_sorted_until(c_alg_internal::c_begin(c),
                              c_alg_internal::c_end(c));
}

template <typename C, typename Compare>
c_alg_internal::ContainerIter<C> c_is_sorted_until(
    C& c, Compare&& comp) {
  return std::is_sorted_until(c_alg_internal::c_begin(c),
                              c_alg_internal::c_end(c),
                              std::forward<Compare>(comp));
}

template <typename RandomAccessContainer>
void c_nth_element(
    RandomAccessContainer& sequence,
    c_alg_internal::ContainerIter<RandomAccessContainer> nth) {
  std::nth_element(c_alg_internal::c_begin(sequence), nth,
                   c_alg_internal::c_end(sequence));
}

template <typename RandomAccessContainer, typename Compare>
void c_nth_element(
    RandomAccessContainer& sequence,
    c_alg_internal::ContainerIter<RandomAccessContainer> nth,
    Compare&& comp) {
  std::nth_element(c_alg_internal::c_begin(sequence), nth,
                   c_alg_internal::c_end(sequence),
                   std::forward<Compare>(comp));
}

// <algorithm> Binary Search

template <typename Sequence, typename T>
c_alg_internal::ContainerIter<Sequence> c_lower_bound(
    Sequence& sequence, T&& value) {
  return std::lower_bound(c_alg_internal::c_begin(sequence),
                          c_alg_internal::c_end(sequence),
                          std::forward<T>(value));
}

template <typename Sequence, typename T, typename Compare>
c_alg_internal::ContainerIter<Sequence> c_lower_bound(
    Sequence& sequence, T&& value, Compare&& comp) {
  return std::lower_bound(c_alg_internal::c_begin(sequence),
                          c_alg_internal::c_end(sequence),
                          std::forward<T>(value), std::forward<Compare>(comp));
}

template <typename Sequence, typename T>
c_alg_internal::ContainerIter<Sequence> c_upper_bound(
    Sequence& sequence, T&& value) {
  return std::upper_bound(c_alg_internal::c_begin(sequence),
                          c_alg_internal::c_end(sequence),
                          std::forward<T>(value));
}

template <typename Sequence, typename T, typename Compare>
c_alg_internal::ContainerIter<Sequence> c_upper_bound(
    Sequence& sequence, T&& value, Compare&& comp) {
  return std::upper_bound(c_alg_internal::c_begin(sequence),
                          c_alg_internal::c_end(sequence),
                          std::forward<T>(value), std::forward<Compare>(comp));
}

template <typename Sequence, typename T>
c_alg_internal::ContainerIterPairType<Sequence, Sequence>
c_equal_range(Sequence& sequence, T&& value) {
  return std::equal_range(c_alg_internal::c_begin(sequence),
                          c_alg_internal::c_end(sequence),
                          std::forward<T>(value));
}

template <typename Sequence, typename T, typename Compare>
c_alg_internal::ContainerIterPairType<Sequence, Sequence>
c_equal_range(Sequence& sequence, T&& value, Compare&& comp) {
  return std::equal_range(c_alg_internal::c_begin(sequence),
                          c_alg_internal::c_end(sequence),
                          std::forward<T>(value), std::forward<Compare>(comp));
}

template <typename Sequence, typename T>
bool c_binary_search(Sequence&& sequence, T&& value) {
  return std::binary_search(c_alg_internal::c_begin(sequence),
                            c_alg_internal::c_end(sequence),
                            std::forward<T>(value));
}

template <typename Sequence, typename T, typename Compare>
bool c_binary_search(Sequence&& sequence, T&& value, Compare&& comp) {
  return std::binary_search(c_alg_internal::c_begin(sequence),
                            c_alg_internal::c_end(sequence),
                            std::forward<T>(value),
                            std::forward<Compare>(comp));
}

// <algorithm> Merge functions

template <typename C1, typename C2, typename OutputIterator>
OutputIterator c_merge(const C1& c1, const C2& c2, OutputIterator result) {
  return std::merge(c_alg_internal::c_begin(c1),
                    c_alg_internal::c_end(c1),
                    c_alg_internal::c_begin(c2),
                    c_alg_internal::c_end(c2), result);
}

template <typename C1, typename C2, typename OutputIterator, typename Compare>
OutputIterator c_merge(const C1& c1, const C2& c2, OutputIterator result,
                       Compare&& comp) {
  return std::merge(c_alg_internal::c_begin(c1),
                    c_alg_internal::c_end(c1),
                    c_alg_internal::c_begin(c2),
                    c_alg_internal::c_end(c2), result,
                    std::forward<Compare>(comp));
}

template <typename C>
void c_inplace_merge(C& c,
                     c_alg_internal::ContainerIter<C> middle) {
  std::inplace_merge(c_alg_internal::c_begin(c), middle,
                     c_alg_internal::c_end(c));
}

template <typename C, typename Compare>
void c_inplace_merge(C& c,
                     c_alg_internal::ContainerIter<C> middle,
                     Compare&& comp) {
  std::inplace_merge(c_alg_internal::c_begin(c), middle,
                     c_alg_internal::c_end(c),
                     std::forward<Compare>(comp));
}

template <typename C1, typename C2>
bool c_includes(const C1& c1, const C2& c2) {
  return std::includes(c_alg_internal::c_begin(c1),
                       c_alg_internal::c_end(c1),
                       c_alg_internal::c_begin(c2),
                       c_alg_internal::c_end(c2));
}

template <typename C1, typename C2, typename Compare>
bool c_includes(const C1& c1, const C2& c2, Compare&& comp) {
  return std::includes(c_alg_internal::c_begin(c1),
                       c_alg_internal::c_end(c1),
                       c_alg_internal::c_begin(c2),
                       c_alg_internal::c_end(c2),
                       std::forward<Compare>(comp));
}

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

// <algorithm> Heap functions

template <typename RandomAccessContainer>
void c_push_heap(RandomAccessContainer& sequence) {
  std::push_heap(c_alg_internal::c_begin(sequence),
                 c_alg_internal::c_end(sequence));
}

template <typename RandomAccessContainer, typename Compare>
void c_push_heap(RandomAccessContainer& sequence, Compare&& comp) {
  std::push_heap(c_alg_internal::c_begin(sequence),
                 c_alg_internal::c_end(sequence),
                 std::forward<Compare>(comp));
}

template <typename RandomAccessContainer>
void c_pop_heap(RandomAccessContainer& sequence) {
  std::pop_heap(c_alg_internal::c_begin(sequence),
                c_alg_internal::c_end(sequence));
}

template <typename RandomAccessContainer, typename Compare>
void c_pop_heap(RandomAccessContainer& sequence, Compare&& comp) {
  std::pop_heap(c_alg_internal::c_begin(sequence),
                c_alg_internal::c_end(sequence),
                std::forward<Compare>(comp));
}

template <typename RandomAccessContainer>
void c_make_heap(RandomAccessContainer& sequence) {
  std::make_heap(c_alg_internal::c_begin(sequence),
                 c_alg_internal::c_end(sequence));
}

template <typename RandomAccessContainer, typename Compare>
void c_make_heap(RandomAccessContainer& sequence, Compare&& comp) {
  std::make_heap(c_alg_internal::c_begin(sequence),
                 c_alg_internal::c_end(sequence),
                 std::forward<Compare>(comp));
}

template <typename RandomAccessContainer>
void c_sort_heap(RandomAccessContainer& sequence) {
  std::sort_heap(c_alg_internal::c_begin(sequence),
                 c_alg_internal::c_end(sequence));
}

template <typename RandomAccessContainer, typename Compare>
void c_sort_heap(RandomAccessContainer& sequence, Compare&& comp) {
  std::sort_heap(c_alg_internal::c_begin(sequence),
                 c_alg_internal::c_end(sequence),
                 std::forward<Compare>(comp));
}

template <typename RandomAccessContainer>
bool c_is_heap(const RandomAccessContainer& sequence) {
  return std::is_heap(c_alg_internal::c_begin(sequence),
                      c_alg_internal::c_end(sequence));
}

template <typename RandomAccessContainer, typename Compare>
bool c_is_heap(const RandomAccessContainer& sequence, Compare&& comp) {
  return std::is_heap(c_alg_internal::c_begin(sequence),
                      c_alg_internal::c_end(sequence),
                      std::forward<Compare>(comp));
}

template <typename RandomAccessContainer>
c_alg_internal::ContainerIter<RandomAccessContainer>
c_is_heap_until(RandomAccessContainer& sequence) {
  return std::is_heap_until(c_alg_internal::c_begin(sequence),
                            c_alg_internal::c_end(sequence));
}

template <typename RandomAccessContainer, typename Compare>
c_alg_internal::ContainerIter<RandomAccessContainer>
c_is_heap_until(RandomAccessContainer& sequence, Compare&& comp) {
  return std::is_heap_until(c_alg_internal::c_begin(sequence),
                            c_alg_internal::c_end(sequence),
                            std::forward<Compare>(comp));
}

// <algorithm> Min/max

template <typename Sequence>
c_alg_internal::ContainerIter<Sequence> c_min_element(
    Sequence& sequence) {
  return std::min_element(c_alg_internal::c_begin(sequence),
                          c_alg_internal::c_end(sequence));
}

template <typename Sequence, typename Compare>
c_alg_internal::ContainerIter<Sequence> c_min_element(
    Sequence& sequence, Compare&& comp) {
  return std::min_element(c_alg_internal::c_begin(sequence),
                          c_alg_internal::c_end(sequence),
                          std::forward<Compare>(comp));
}

template <typename Sequence>
c_alg_internal::ContainerIter<Sequence> c_max_element(
    Sequence& sequence) {
  return std::max_element(c_alg_internal::c_begin(sequence),
                          c_alg_internal::c_end(sequence));
}

template <typename Sequence, typename Compare>
c_alg_internal::ContainerIter<Sequence> c_max_element(
    Sequence& sequence, Compare&& comp) {
  return std::max_element(c_alg_internal::c_begin(sequence),
                          c_alg_internal::c_end(sequence),
                          std::forward<Compare>(comp));
}

template <typename C>
c_alg_internal::ContainerIterPairType<C, C>
c_minmax_element(C& c) {
  return std::minmax_element(c_alg_internal::c_begin(c),
                             c_alg_internal::c_end(c));
}

template <typename C, typename Compare>
c_alg_internal::ContainerIterPairType<C, C>
c_minmax_element(C& c, Compare&& comp) {
  return std::minmax_element(c_alg_internal::c_begin(c),
                             c_alg_internal::c_end(c),
                             std::forward<Compare>(comp));
}

// <algorithm> Lexicographical Comparisons

template <typename Sequence1, typename Sequence2>
bool c_lexicographical_compare(Sequence1&& sequence1, Sequence2&& sequence2) {
  return std::lexicographical_compare(
      c_alg_internal::c_begin(sequence1),
      c_alg_internal::c_end(sequence1),
      c_alg_internal::c_begin(sequence2),
      c_alg_internal::c_end(sequence2));
}

template <typename Sequence1, typename Sequence2, typename Compare>
bool c_lexicographical_compare(Sequence1&& sequence1, Sequence2&& sequence2,
                               Compare&& comp) {
  return std::lexicographical_compare(
      c_alg_internal::c_begin(sequence1),
      c_alg_internal::c_end(sequence1),
      c_alg_internal::c_begin(sequence2),
      c_alg_internal::c_end(sequence2),
      std::forward<Compare>(comp));
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

// <numeric> algorithms

template <typename Sequence, typename T>
void c_iota(Sequence& sequence, T&& value) {
  std::iota(c_alg_internal::c_begin(sequence),
            c_alg_internal::c_end(sequence),
            std::forward<T>(value));
}
template <typename Sequence, typename T>
std::decay_t<T> c_accumulate(const Sequence& sequence, T&& init) {
  return std::accumulate(c_alg_internal::c_begin(sequence),
                         c_alg_internal::c_end(sequence),
                         std::forward<T>(init));
}

template <typename Sequence, typename T, typename BinaryOp>
std::decay_t<T> c_accumulate(const Sequence& sequence, T&& init,
                             BinaryOp&& binary_op) {
  return std::accumulate(c_alg_internal::c_begin(sequence),
                         c_alg_internal::c_end(sequence),
                         std::forward<T>(init),
                         std::forward<BinaryOp>(binary_op));
}

template <typename Sequence1, typename Sequence2, typename T>
std::decay_t<T> c_inner_product(const Sequence1& factors1,
                                const Sequence2& factors2,
                                T&& sum) {
  return std::inner_product(c_alg_internal::c_begin(factors1),
                            c_alg_internal::c_end(factors1),
                            c_alg_internal::c_begin(factors2),
                            std::forward<T>(sum));
}

template <typename Sequence1, typename Sequence2, typename T,
          typename BinaryOp1, typename BinaryOp2>
std::decay_t<T> c_inner_product(const Sequence1& factors1,
                                const Sequence2& factors2,
                                T&& sum, BinaryOp1&& op1, BinaryOp2&& op2) {
  return std::inner_product(c_alg_internal::c_begin(factors1),
                            c_alg_internal::c_end(factors1),
                            c_alg_internal::c_begin(factors2),
                            std::forward<T>(sum), std::forward<BinaryOp1>(op1),
                            std::forward<BinaryOp2>(op2));
}

template <typename InputSequence, typename OutputIt>
OutputIt c_adjacent_difference(const InputSequence& input,
                               OutputIt output_first) {
  return std::adjacent_difference(c_alg_internal::c_begin(input),
                                  c_alg_internal::c_end(input),
                                  output_first);
}

template <typename InputSequence, typename OutputIt, typename BinaryOp>
OutputIt c_adjacent_difference(const InputSequence& input,
                               OutputIt output_first, BinaryOp&& op) {
  return std::adjacent_difference(c_alg_internal::c_begin(input),
                                  c_alg_internal::c_end(input),
                                  output_first, std::forward<BinaryOp>(op));
}

template <typename InputSequence, typename OutputIt>
OutputIt c_partial_sum(const InputSequence& input, OutputIt output_first) {
  return std::partial_sum(c_alg_internal::c_begin(input),
                          c_alg_internal::c_end(input),
                          output_first);
}

template <typename InputSequence, typename OutputIt, typename BinaryOp>
OutputIt c_partial_sum(const InputSequence& input, OutputIt output_first,
                       BinaryOp&& op) {
  return std::partial_sum(c_alg_internal::c_begin(input),
                          c_alg_internal::c_end(input),
                          output_first, std::forward<BinaryOp>(op));
}

#endif
