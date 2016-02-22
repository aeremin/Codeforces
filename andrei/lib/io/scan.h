// Input functions. Come in several flavours:
//
// * try_scan<T>
//   Reads T from standard input, sets success bit.
//   If the call had failed, the retuned value is undefined.
//   For convenience has alias called try_scan_T,
//   expect (T == std::string) where the alias is try_scan_word.
//   TODO: Consider:
//           - swapping arguments (set variable, return success)
//           - using optionals instead
//
// * scan<T>
//   Reads T from standard input. Abort on failure.
//   For convenience has alias called scan_T,
//   expect (T == std::string) where the alias is scan_word.
//
// * scan
//   Automagically reads any type from standard input.
//   Can be used like this: ``int x = scan();  foo(scan());''
//   Abort on failure.
//
// * SCAN_2, SCAN_3, ...
//   Returns a brace-enclosed sequence of N object that can be used
//   to call an N-argument constructor:
//   ``Foo f = SCAN_3();  vec.push_back(SCAN_2());''
//   To call an explicit constructor put SCAN_x next to the type name:
//   ``Foo f SCAN_3();  vec.push_back(Bar SCAN_2());''
//   WARNING: Doesn't work in gcc < 4.9.1 and in MSVC (see below) -
//            execution order is not defined.
//            TODO: Check clang.
//            TODO: Add compile-time checks.
//
// * scan(...)
//   Scans one of more values from the input.
//   Abort if at least one element cannot be read.
//
// * scan_vector(n), scan_vector_2(n), scan_vector_3(n), ...
//   Returns vector of n elements, each requiring the corresponding
//   number of arguments to construct.
//   WARNING: scan_vector_K versions inherit SCAN_K limitations.
//
// Supported types are:
//
// * int, uint, int64, uint64
//   A decimal representation of an integer.
//
// * float, double
//   A decimal representation of a floating-point number,
//   either in fixed or in exponential format.
//
// * char
//   An ASCII character.
//
// * std::string
//   A word, i.e. a sequence of characters surrounded by whitespace.
//   Leading whitespace is ignored.
//
// * line (std::string)
//   A sequence of characters up to a new-line character.
//   Leading "\n" are ignored; leading whitespace is not.
//   Trailing "\n" is consumed, but not included in the result.
//
// TODO: Execution order warning.
//
// WARNING. Scan functions rely both on cstdio (for chars, integers and floats)
//          and iostream (for strings), so std::ios_base::sync_with_stdio must
//          remain true!

#pragma once

#include <cinttypes>
#include <cstdio>
#include <iostream>
#include <limits>
#include <string>
#include <tuple>

#include "iter/for_times.h"
#include "util/check.h"
#include "util/types.h"


#define DEFINE_SIMPLE_SCAN_TYPE(TYPE_NAME, FORMAT)  \
  template<>  \
  TYPE_NAME try_scan<TYPE_NAME>(bool& success) {  \
    TYPE_NAME result;  \
    success = (scanf(FORMAT, &result) > 0);  \
    return result;  \
  }

#ifdef LOCAL_PC

// Use iostream locally for redirections in unit tests
// TODO: Add checks so that it doesn't compile for unsupported types.
template<typename T>
T try_scan(bool& success) {
    T result;
    success = bool(std::cin >> result);
    return result;
}

#else

template<typename T>
T try_scan(bool& success);

// Use stdio remotely, because it's faster
DEFINE_SIMPLE_SCAN_TYPE(int, "%d");
DEFINE_SIMPLE_SCAN_TYPE(uint, "%u");
DEFINE_SIMPLE_SCAN_TYPE(int64, "%" SCNd64);
DEFINE_SIMPLE_SCAN_TYPE(uint64, "%" SCNu64);
DEFINE_SIMPLE_SCAN_TYPE(float, "%f");
DEFINE_SIMPLE_SCAN_TYPE(double, "%lf");
DEFINE_SIMPLE_SCAN_TYPE(char, "%c");  // TODO: sync with iostream (in terms of whitespace treatment)

template<>
std::string try_scan<std::string>(bool& success) {
    std::string result;
    success = bool(std::cin >> result);
    return result;
}

#endif

#if 0  // TODO try
template<typename Arg>
std::tuple<Arg> try_scan<std::tuple<Arg>>(bool& success) {
    return std::make_tuple(try_scan<Arg>(success));
}

template<typename Head, typename... Tail>
std::tuple<Head, Tail> try_scan<std::tuple<Head, Tail>>(bool& success) {
    auto head = try_scan<Head>(success);
    if (!success)
        return {};
    auto tail = try_scan<Tail>(success);
    return std::tuple_cat(head, tail);
}
#endif

inline int try_scan_int(bool& success)          { return try_scan<int>(success);    }
inline uint try_scan_uint(bool& success)        { return try_scan<uint>(success);   }
inline int64 try_scan_int64(bool& success)      { return try_scan<int64>(success);  }
inline uint64 try_scan_uint64(bool& success)    { return try_scan<uint64>(success); }
inline float try_scan_float(bool& success)      { return try_scan<float>(success);  }
inline double try_scan_double(bool& success)    { return try_scan<double>(success); }
inline char try_scan_char(bool& success)        { return try_scan<char>(success);   }
inline std::string try_scan_word(bool& success) { return try_scan<std::string>(success); }

inline std::string try_scan_line(bool& success) {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string result;
    success = bool(std::getline(std::cin, result));
    return result;
}


template<typename T>
T scan() {
    bool success = false;
    T result = try_scan<T>(success);
    CHECK(success);
    return result;
}

inline int scan_int()           { return scan<int>();    }
inline uint scan_uint()         { return scan<uint>();   }
inline int64 scan_int64()       { return scan<int64>();  }
inline uint64 scan_uint64()     { return scan<uint64>(); }
inline float scan_float()       { return scan<float>();  }
inline double scan_double()     { return scan<double>(); }
inline char scan_char()         { return scan<char>();   }
inline std::string scan_word()  { return scan<std::string>(); }

inline std::string scan_line() {
    bool success = false;
    std::string result = try_scan_line(success);
    CHECK(success);
    return result;
}


class ScanResult {
public:
    ScanResult(const ScanResult&) = delete;
    ScanResult& operator=(const ScanResult&) = delete;
    ScanResult(ScanResult&&) = delete;
    ScanResult& operator=(ScanResult&&) = delete;

    template<typename T>
    operator T() && {
        return scan<T>();
    }
};

ScanResult scan() {
    return {};
}

// TODO: fix for std::string
#define SCAN_2()  {scan(), scan()}
#define SCAN_3()  {scan(), scan(), scan()}
#define SCAN_4()  {scan(), scan(), scan(), scan()}
#define SCAN_5()  {scan(), scan(), scan(), scan(), scan()}
#define SCAN_6()  {scan(), scan(), scan(), scan(), scan(), scan()}
#define SCAN_7()  {scan(), scan(), scan(), scan(), scan(), scan(), scan()}
#define SCAN_8()  {scan(), scan(), scan(), scan(), scan(), scan(), scan(), scan()}


template<typename Arg>
void scan(Arg& arg) {
    arg = scan<Arg>();
}

template<typename Head, typename... Tail>
void scan(Head& head, Tail&... tail) {
    scan(head);
    scan(tail...);
}

#define DEFINE_SCAN_VECTOR_N(NAME, SCAN_FUNCTION)  \
template<typename ElementT>  \
std::vector<ElementT> NAME(size_t n_elements) {  \
    CHECK(ssize_t(n_elements) >= 0);  \
    std::vector<ElementT> result;  \
    result.reserve(n_elements);  \
    FOR_TIMES(n_elements) {  \
        result.push_back(SCAN_FUNCTION);  \
    }  \
    return result;  \
}

DEFINE_SCAN_VECTOR_N(scan_vector, scan())
DEFINE_SCAN_VECTOR_N(scan_vector_2, SCAN_2())
DEFINE_SCAN_VECTOR_N(scan_vector_3, SCAN_3())
DEFINE_SCAN_VECTOR_N(scan_vector_4, SCAN_4())
DEFINE_SCAN_VECTOR_N(scan_vector_5, SCAN_5())
DEFINE_SCAN_VECTOR_N(scan_vector_6, SCAN_6())
DEFINE_SCAN_VECTOR_N(scan_vector_7, SCAN_7())
DEFINE_SCAN_VECTOR_N(scan_vector_8, SCAN_8())

#undef DEFINE_SCAN_VECTOR_N
