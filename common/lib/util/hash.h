// Defines hash for std::tuple and allows to quickly define hash functions.
//
// DEFINE_HASH_n(class, field_1, ... field_n) defines std::hash<class>.
//
// field_k can be either a public data field or a constant function.
//
// The hash function applies std::hash to each field and combines the results.
// If STL doesn't provide hash function for one of the field, you can either
// define it directly, or use another DEFINE_HASH_n.

#pragma once

#include <climits>
#include <functional>

#include "util/macro.h"


namespace std {
    namespace {
        // Code from boost

        template <class T>
        inline void hash_combine(std::size_t& seed, T const& v) {
            seed ^= std::hash<T>()(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
        }

        template <class Tuple, size_t Index = std::tuple_size<Tuple>::value - 1>
        struct HashValueImpl {
          static void apply(size_t& seed, Tuple const& tuple) {
            HashValueImpl<Tuple, Index-1>::apply(seed, tuple);
            hash_combine(seed, std::get<Index>(tuple));
          }
        };

        template <class Tuple>
        struct HashValueImpl<Tuple,0> {
          static void apply(size_t& seed, Tuple const& tuple) {
            hash_combine(seed, std::get<0>(tuple));
          }
        };
    }

    template <typename ... TT>
    struct hash<std::tuple<TT...>> {
        size_t operator()(std::tuple<TT...> const& tt) const {
            size_t seed = 0;
            HashValueImpl<std::tuple<TT...> >::apply(seed, tt);
            return seed;
        }

    };
}


template<typename... Args>
size_t mixed_hash(const Args&... args) {
    return std::hash<std::tuple<const Args&...>>()(std::tie(args...));
}


#define DEFINE_HASH_ABSTRACT(TYPE_NAME, ARGS_LIST)    \
    namespace std {    \
        template<>struct hash<TYPE_NAME> {    \
            size_t operator()(const TYPE_NAME& a) const { return mixed_hash(ARGS_LIST); }    \
        };    \
    }

// TODO: fix: still can't put into onordered_set without ==

#define DEFINE_HASH_1(TYPE_NAME, FIELD1)    \
    DEFINE_HASH_ABSTRACT(TYPE_NAME, a.FIELD1)

#define DEFINE_HASH_2(TYPE_NAME, FIELD1, FIELD2)    \
    DEFINE_HASH_ABSTRACT(TYPE_NAME, a.FIELD1 COMMA a.FIELD2)

#define DEFINE_HASH_3(TYPE_NAME, FIELD1, FIELD2, FIELD3)    \
    DEFINE_HASH_ABSTRACT(TYPE_NAME, a.FIELD1 COMMA a.FIELD2 COMMA a.FIELD3)

#define DEFINE_HASH_4(TYPE_NAME, FIELD1, FIELD2, FIELD3, FIELD4)    \
    DEFINE_HASH_ABSTRACT(TYPE_NAME, a.FIELD1 COMMA a.FIELD2 COMMA a.FIELD3 COMMA a.FIELD4)
