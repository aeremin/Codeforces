#pragma once
#include <stdint.h>

inline bool isPrime( uint64_t n )
{
    if ( n == 1 )
        return false;
    if ( n == 2 )
        return true;
    if ( n % 2 == 0 )
        return false;
    for ( uint64_t div = 3; div * div <= n; div += 2 )
        if ( n % div == 0 )
            return false;
    return true;
}

//! Generates primes in segment [1, upperBound]
//! Returned vector is guaranteed to be sorted.
inline std::vector<uint64_t> generatePrimesUntil( uint64_t upperBound )
{
    if ( upperBound < 2 )
        return{};

    std::vector<uint64_t> result = { 2 };
    for ( uint64_t candidate = 3; candidate <= upperBound; candidate += 2 )
    {
        bool divisibleByPrevious = false;
        for ( size_t divisorIndex = 1; divisorIndex < result.size() && result[divisorIndex] * result[divisorIndex] <= candidate; ++divisorIndex )
        {
            if ( candidate % result[divisorIndex] == 0 )
            {
                divisibleByPrevious = true;
                break;
            }
        }

        if ( !divisibleByPrevious )
            result.push_back( candidate );
    }

    return result;
}