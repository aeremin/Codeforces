#pragma once
#include <stdint.h>
#include "Sign.hpp"
#include <utility>

namespace
{
inline uint64_t gcdInternal( uint64_t a, uint64_t b )
{
    if ( b == 0 )
        return a;
    
    return gcdInternal( b, a % b );
}

inline uint64_t gcdDecompositionInternal( uint64_t a, uint64_t b, int64_t& x, int64_t& y )
{
    if ( b == 0 )
    {
        x = 1;
        y = 0;
        return a;
    }

    int64_t xx, yy;
    auto gcd = gcdDecompositionInternal( b, a % b, xx, yy );
    // ok, gcd = xx * b + (a % b) * yy = xx * b + (a - (a / b) * b) * yy =
    //         = b * (xx - (a / b) * yy) + a * yy
    x = yy;
    y = xx - ( a / b ) * yy;
    return gcd;
}

}

inline uint64_t greatestCommonDivisor( int64_t a, int64_t b )
{
    a *= sgn( a );
    b *= sgn( b );
    if ( a < b )
        std::swap( a, b );
    return gcdInternal( a, b );
}

inline uint64_t gcdDecomposition( int64_t a, int64_t b, int64_t& x, int64_t& y )
{
    auto aUnsigned = a * sgn( a );
    auto bUnsigned = b * sgn( b );
    auto gcd = ( aUnsigned < bUnsigned ) ? gcdDecompositionInternal( aUnsigned, bUnsigned, x, y ) : gcdDecompositionInternal( bUnsigned, aUnsigned, y, x );
    x *= sgn( a );
    y *= sgn( b );
    return gcd;
}