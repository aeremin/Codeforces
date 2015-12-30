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
}

inline uint64_t greatestCommonDivisor( int64_t a, int64_t b )
{
    a *= sgn( a );
    b *= sgn( b );
    if ( a < b )
        std::swap( a, b );
    return gcdInternal( a, b );
}