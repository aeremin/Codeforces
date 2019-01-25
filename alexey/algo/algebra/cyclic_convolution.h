#pragma once
#include <cassert>
#include <complex>
#include <vector>

#include "algo/numbertheory/Residue.hpp"
#include "algo/polynomial/fast_multiplication.h"
#include "algo/polynomial/polynomial.h"

namespace internal {
template <typename T>
struct ToComplex {
    static std::complex<double> convert(const T& v) { return v; }
};

template <typename UnderlyingInt, UnderlyingInt MOD>
struct ToComplex<Residue<UnderlyingInt, MOD>> {
    static std::complex<double> convert(const Residue<UnderlyingInt, MOD>& v) { return v.rep(); }
};

template <typename T>
struct FromComplex {
    static T convert(const std::complex<double>& v) { return v; }
};

template <>
struct FromComplex<double> {
    static double convert(const std::complex<double>& v) { return v.real(); }
};

template <typename UnderlyingInt, UnderlyingInt MOD>
struct FromComplex<Residue<UnderlyingInt, MOD>> {
    static Residue<UnderlyingInt, MOD> convert(const std::complex<double>& v) { return v.real() + 0.5; }
};

template <>
struct FromComplex<int> {
    static int convert(const std::complex<double>& v) { return (v.real() > 0) ? v.real() + 0.5 : v.real() - 0.5; }
};

template <>
struct FromComplex<int64_t> {
    static int convert(const std::complex<double>& v) { return (v.real() > 0) ? v.real() + 0.5 : v.real() - 0.5; }
};
}  // namespace internal

// Complexity is O(n ln n)
template <typename T>
std::vector<T> CyclicConvolution(const std::vector<T>& a, const std::vector<T>& b) {
    assert(a.size() == b.size());
    auto n = a.size();

    std::vector<std::complex<double>> aComplexified(n), bComplexified(2 * n);
    for (auto i : range(n)) {
        aComplexified[i] = internal::ToComplex<T>::convert(a[i]);
        bComplexified[i] = bComplexified[i + n] = internal::ToComplex<T>::convert(b[i]);
    }
    Polynomial<std::complex<double>> p(std::move(aComplexified)), q(std::move(bComplexified));
    auto r = FastMultiplication(std::move(p), std::move(q));
    std::vector<T> result(n);
    for (auto i : range(n))
        result[i] = internal::FromComplex<T>::convert(r.coefficient(n + i));
    return result;
}