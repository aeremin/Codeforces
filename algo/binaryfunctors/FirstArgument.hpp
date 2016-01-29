#pragma once
#include <algorithm>

namespace binaryFunctors
{

template<typename T>
struct FirstArgument
{
    T operator()(const T& t, const T& u) const { return t; }
};


}