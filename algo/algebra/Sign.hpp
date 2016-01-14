#pragma once

template <typename T> int64_t sgn( T val )
{
    return ( T( 0 ) < val ) - ( val < T( 0 ) );
}