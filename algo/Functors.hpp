#pragma once
#include <algorithm>

namespace binaryFunctors
{

template<typename T>
struct Sum
{
    T operator()(const T& t, const T& u) const { return t + u; }
};

template<typename T>
struct Min
{
    T operator()(const T& t, const T& u) const { return std::min(t, u); }
};

template<typename T>
struct Max
{
    T operator()(const T& t, const T& u) const { return std::max(t, u); }
};

struct Or
{
    uint64_t operator()(uint64_t t, uint64_t u) const { return t | u; }
};

struct And
{
    uint64_t operator()(uint64_t t, uint64_t u) const { return t & u; }
};

struct Xor
{
    uint64_t operator()(uint64_t t, uint64_t u) const { return t ^ u; }
};


}