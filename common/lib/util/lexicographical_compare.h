// Macros to quickly define lexicographical comparison operators.
//
// DEFINE_LEXICOGRAPHICAL_COMPARISON_n(class, field_1, ... field_n) defines
// all 6 comparison operators: ==, !=, <, >, <=, >=.
//
// field_k can be either a public data field or a constant function.
//
// Each comparison operator evaluates every field exactly once.
// There is no short-circuit evaluation, i.e. comparison will still evaluate
// second field if the first one is already different.
//
// TODO: Consider writting short-circuit comparison.

#pragma once

#include "util/macro.h"


#define DEFINE_LEXICOGRAPHICAL_COMPARISON_ABSTRACT(TYPE_NAME, ARGS_LIST_1, ARGS_LIST_2)                                \
    bool operator==(const TYPE_NAME& a, const TYPE_NAME& b) { return std::tie(ARGS_LIST_1) == std::tie(ARGS_LIST_2); } \
    bool operator!=(const TYPE_NAME& a, const TYPE_NAME& b) { return std::tie(ARGS_LIST_1) != std::tie(ARGS_LIST_2); } \
    bool operator<(const TYPE_NAME& a, const TYPE_NAME& b) { return std::tie(ARGS_LIST_1) < std::tie(ARGS_LIST_2); }   \
    bool operator>(const TYPE_NAME& a, const TYPE_NAME& b) { return std::tie(ARGS_LIST_1) > std::tie(ARGS_LIST_2); }   \
    bool operator<=(const TYPE_NAME& a, const TYPE_NAME& b) { return std::tie(ARGS_LIST_1) <= std::tie(ARGS_LIST_2); } \
    bool operator>=(const TYPE_NAME& a, const TYPE_NAME& b) { return std::tie(ARGS_LIST_1) >= std::tie(ARGS_LIST_2); }

#define DEFINE_LEXICOGRAPHICAL_COMPARISON_1(TYPE_NAME, FIELD1) \
    DEFINE_LEXICOGRAPHICAL_COMPARISON_ABSTRACT(TYPE_NAME, a.FIELD1, b.FIELD1)

#define DEFINE_LEXICOGRAPHICAL_COMPARISON_2(TYPE_NAME, FIELD1, FIELD2) \
    DEFINE_LEXICOGRAPHICAL_COMPARISON_ABSTRACT(TYPE_NAME, a.FIELD1 COMMA a.FIELD2, b.FIELD1 COMMA b.FIELD2)

#define DEFINE_LEXICOGRAPHICAL_COMPARISON_3(TYPE_NAME, FIELD1, FIELD2, FIELD3)                    \
    DEFINE_LEXICOGRAPHICAL_COMPARISON_ABSTRACT(TYPE_NAME, a.FIELD1 COMMA a.FIELD2 COMMA a.FIELD3, \
                                               b.FIELD1 COMMA b.FIELD2 COMMA b.FIELD3)

#define DEFINE_LEXICOGRAPHICAL_COMPARISON_4(TYPE_NAME, FIELD1, FIELD2, FIELD3, FIELD4)                           \
    DEFINE_LEXICOGRAPHICAL_COMPARISON_ABSTRACT(TYPE_NAME, a.FIELD1 COMMA a.FIELD2 COMMA a.FIELD3 COMMA a.FIELD4, \
                                               b.FIELD1 COMMA b.FIELD2 COMMA b.FIELD3 COMMA b.FIELD4)
