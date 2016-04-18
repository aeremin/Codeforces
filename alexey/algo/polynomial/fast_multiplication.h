#pragma once
#include <complex>
#include "algo/polynomial/fast_fourier_transform.h"
template<typename T>
inline Polynomial<std::complex<T>> FastMultiplication(Polynomial<std::complex<T>> lh, Polynomial<std::complex<T>> rh) {
    auto maxDegree = lh.formal_degree() + rh.formal_degree();
    int lgDegree = 0;
    while ((1 << lgDegree) <= maxDegree)
        ++lgDegree;
    lh.set_coefficient((1 << lgDegree) - 1, 0);
    rh.set_coefficient((1 << lgDegree) - 1, 0);

    auto lhFFT = FastFourierTransform(std::move(lh), false);
    auto rhFFT = FastFourierTransform(std::move(rh), false);
    for (int i : range(lhFFT.formal_degree() + 1))
        lhFFT.coefficient(i) *= rhFFT.coefficient(i);
    return FastFourierTransform(std::move(lhFFT), true);
}