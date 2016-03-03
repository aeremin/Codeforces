#pragma once
#include <complex>
#include "algo/polynomial/polynomial.h"

Polynomial<complex<double>> operator*(Polynomial<complex<double>> lh, Polynomial<complex<double>> rh) {
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