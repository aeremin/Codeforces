#pragma once
#include <array>

template<typename T, size_t Dimensions>
std::array<T, (1 << Dimensions)> calculatePrefixSums(std::array<T, (1 << Dimensions)> values)
{
    for (size_t d = 0; d < Dimensions; ++d)
        for (size_t i = 0; i < (1 << Dimensions); ++i)
            if (i & (1 << d))
                values[i] += values[i ^ (1 << d)];
    return values;
}

template<typename T, size_t Dimensions>
std::array<T, (1 << Dimensions)> calculateValuesByPrefixSums(std::array<T, (1 << Dimensions)> values)
{
    for (size_t d = 0; d < Dimensions; ++d)
        for (size_t i = 0; i < (1 << Dimensions); ++i)
            if (i & (1 << d))
                values[i] -= values[i ^ (1 << d)];
    return values;
}
