#pragma once
#include <complex>
#include "algo/polynomial/polynomial.h"
#include "math/pi.h"

int rev( int num, int lg_n ) {
    int res = 0;
    for ( int i = 0; i < lg_n; ++i )
        if ( num & ( 1 << i ) )
            res |= 1 << ( lg_n - 1 - i );
    return res;
}

// Formal degree of p must be of form n = 2^k - 1.
// Time complexity is O(2^k * k) = O(n lg n).
// Additional space is O(1).
Polynomial<std::complex<double>> FastFourierTransform( Polynomial<std::complex<double>> p, bool invert ) {
    int n = p.formal_degree() + 1;
    int lg_n = 0;
    while ( ( 1 << lg_n ) < n ) ++lg_n;
    assert( ( 1 << lg_n ) == n );

    for ( int i : range( n ) ) {
        auto iReversed = rev( i, lg_n );
        if ( i < iReversed )
            std::swap( p.coefficient( i ), p.coefficient( iReversed ) );
    }

    for ( int len = 2; len <= n; len *= 2 ) {
        double ang = 2 * kPi / len * ( invert ? -1 : 1 );
        std::complex<double> wlen( cos( ang ), sin( ang ) );
        for ( int i = 0; i < n; i += len ) {
            std::complex<double> w = 1.0;
            for ( int j : range(len / 2) ) {
                auto u = p.coefficient( i + j );
                auto v = p.coefficient( i + j + len / 2 ) * w;
                p.coefficient( i + j ) = u + v;
                p.coefficient( i + j + len / 2 ) = u - v;
                w *= wlen;
            }
        }
    }

    if ( invert )
        p *= std::complex<double>(1.0 / n);

    return p;
}