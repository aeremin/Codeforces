// Macros allowing to quickly define hash function and comparison operators.
//
// DEFINE_COMPARISON_AND_HASH_n(class, field_1, ... field_n) defines:
//   - an element-wise hash function
//   - all 6 comparison operators (==, !=, <, >, <=, >=)
//
// field_k can be either a public data field or a constant function.
//
// The hash function applies std::hash to each field and combines the results.
// If STL doesn't provide hash function for one of the field, you can either
// define it directly, or use another DEFINE_COMPARISON_AND_HASH_n.
//
// Comparison is lexicographical.
//
// Both hash and comparison evaluate each field exactly once.
// There is no short-circuit evaluation, i.e. comparison will still evaluate
// second field if the first one is already different.
//
// TODO: Compare my hash with boost::hash_combine.
// TODO: Compare my hash with Cantor pairing function.
// TODO: Consider writting short-circuit comparison.

#pragma once

#include <climits>
#include <functional>

#include "util/macro.h"


template<typename Arg>
size_t mixed_hash(Arg&& arg) {
    return std::hash<typename std::decay<Arg>::type>()(std::forward<Arg>(arg));
}

template<typename First, typename Second>
size_t mixed_hash(First&& first, Second&& second) {
    constexpr unsigned shift_left = 23;
    constexpr unsigned shift_right = sizeof(size_t) * CHAR_BIT - shift_left;
    const size_t first_hash = mixed_hash(std::forward<First>(first));
    const size_t second_hash = mixed_hash(std::forward<Second>(second));
    return first_hash ^ (second_hash << shift_left) ^ (second_hash >> shift_right) ^ 0x9e3779b9;
}

template<typename Head, typename... Tail>
size_t mixed_hash(Head&& head, Tail&&... tail) {
    return mixed_hash(std::forward<Head>(head), mixed_hash(std::forward<Tail>(tail)...));
}


#define DEFINE_COMPARISON_AND_HASH_ABSTRACT(TYPE_NAME, ARGS_LIST_1, ARGS_LIST_2)    \
    bool operator==(const TYPE_NAME& a, const TYPE_NAME& b)  { return std::tie(ARGS_LIST_1) == std::tie(ARGS_LIST_2); }    \
    bool operator!=(const TYPE_NAME& a, const TYPE_NAME& b)  { return std::tie(ARGS_LIST_1) != std::tie(ARGS_LIST_2); }    \
    bool operator< (const TYPE_NAME& a, const TYPE_NAME& b)  { return std::tie(ARGS_LIST_1) <  std::tie(ARGS_LIST_2); }    \
    bool operator> (const TYPE_NAME& a, const TYPE_NAME& b)  { return std::tie(ARGS_LIST_1) >  std::tie(ARGS_LIST_2); }    \
    bool operator<=(const TYPE_NAME& a, const TYPE_NAME& b)  { return std::tie(ARGS_LIST_1) <= std::tie(ARGS_LIST_2); }    \
    bool operator>=(const TYPE_NAME& a, const TYPE_NAME& b)  { return std::tie(ARGS_LIST_1) >= std::tie(ARGS_LIST_2); }    \
    namespace std {    \
        template<>struct hash<TYPE_NAME> {    \
            size_t operator()(const TYPE_NAME& a) const { return mixed_hash(ARGS_LIST_1); }    \
        };    \
    }

#define DEFINE_COMPARISON_AND_HASH_1(TYPE_NAME, FIELD1)    \
    DEFINE_COMPARISON_AND_HASH_ABSTRACT(TYPE_NAME, a.FIELD1, b.FIELD1)

#define DEFINE_COMPARISON_AND_HASH_2(TYPE_NAME, FIELD1, FIELD2)    \
    DEFINE_COMPARISON_AND_HASH_ABSTRACT(TYPE_NAME, a.FIELD1 COMMA a.FIELD2, b.FIELD1 COMMA b.FIELD2)

#define DEFINE_COMPARISON_AND_HASH_3(TYPE_NAME, FIELD1, FIELD2, FIELD3)    \
    DEFINE_COMPARISON_AND_HASH_ABSTRACT(TYPE_NAME, a.FIELD1 COMMA a.FIELD2 COMMA a.FIELD3, b.FIELD1 COMMA b.FIELD2 COMMA b.FIELD3)

#define DEFINE_COMPARISON_AND_HASH_4(TYPE_NAME, FIELD1, FIELD2, FIELD3, FIELD4)    \
    DEFINE_COMPARISON_AND_HASH_ABSTRACT(TYPE_NAME, a.FIELD1 COMMA a.FIELD2 COMMA a.FIELD3 COMMA a.FIELD4, b.FIELD1 COMMA b.FIELD2 COMMA b.FIELD3 COMMA b.FIELD4)
