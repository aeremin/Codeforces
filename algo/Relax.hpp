#pragma once
#include <algorithm>

template<typename T>
void relaxMax(T& relaxWhat, const T& relaxBy)
{
    relaxWhat = std::max(relaxWhat, relaxBy);
}

template<typename T>
void relaxMin(T& relaxWhat, const T& relaxBy)
{
    relaxWhat = std::min( relaxWhat, relaxBy );
}