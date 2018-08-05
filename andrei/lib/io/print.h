// Output functions.
//
// Print values to the standard output.
//
// * print(value1, [value2, [...]])
//   Prints one or more values.
//
// * print_ln([value1, [value2, [...]]])
//   Prints zero or more values and a newline character.
//
// * print_vec(vec, separator)
//   Prints all elements in container 'vec', separated by 'separator'.
//
// * print_vec_ln(vec, separator)
//   Prints all elements in container 'vec', separated by 'separator',
//   and a new line character.

#pragma once

#include <cstdio>
#include <iomanip>
#include <iostream>
#include <string>

#include "util/macro.h"


#define FLOAT_OUTPUT_PRECISION 12


#define FLOAT_OUTPUT_PRECISION_STR STRINGIFY(FLOAT_OUTPUT_PRECISION)

#define DEFINE_SIMPLE_PRINT_TYPE(TYPE_NAME, FORMAT)  \
    template<>  \
    void print<TYPE_NAME>(const TYPE_NAME& value) {  \
        printf(FORMAT, value);  \
    }

#ifdef LOCAL_PC

// Use iostream locally for redirections in unit tests
// TODO: Add checks so that it doesn't compile for unsupported types.
template<typename T>
void print(const T& value) {
    std::cout << std::fixed << std::setprecision(FLOAT_OUTPUT_PRECISION) << value;
}

#else

template<typename T>
void print(const T& value);

// Use stdio remotely, because it's faster
DEFINE_SIMPLE_PRINT_TYPE(int, "%d");
DEFINE_SIMPLE_PRINT_TYPE(uint, "%u");
DEFINE_SIMPLE_PRINT_TYPE(int64, "%" PRId64);
DEFINE_SIMPLE_PRINT_TYPE(uint64, "%" PRIu64);
DEFINE_SIMPLE_PRINT_TYPE(float, "%." FLOAT_OUTPUT_PRECISION_STR "f");
DEFINE_SIMPLE_PRINT_TYPE(double, "%." FLOAT_OUTPUT_PRECISION_STR "lf");
DEFINE_SIMPLE_PRINT_TYPE(char, "%c");

template<>  \
void print<std::string>(const std::string& value) {
    printf("%s", value.c_str());
}

#endif


inline void print_ln() {
    print('\n');
}

template<typename T>
void print_ln(const T& value) {
    print(value);
    print_ln();
}


template<typename HeadT, typename... TailT>
void print(const HeadT& head, const TailT&... tail) {
    print(head);
    print(tail...);
}

template<typename HeadT, typename... TailT>
void print_ln(const HeadT& head, const TailT&... tail) {
    print(head);
    print_ln(tail...);
}


template<typename VectorT, typename SeparatorT = char>
void print_vector(const VectorT& vec, const SeparatorT& separator = ' ') {
    if (vec.empty())
        return;
    const auto end_it = std::prev(end(vec));
    for (auto it = begin(vec); it != end_it; ++it) {
        print(*it);
        print(separator);
    }
    print(*end_it);
}

template<typename VectorT, typename SeparatorT = char>
void print_vector_ln(const VectorT& vec, const SeparatorT& separator = ' ') {
    print_vector(vec, separator);
    print_ln();
}
