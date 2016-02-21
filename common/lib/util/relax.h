#pragma once
#include <algorithm>

template<typename T>
void relax_max(T& relaxWhat, const T& relaxBy) {
    relaxWhat = std::max(relaxWhat, relaxBy);
}

template<typename T>
void relax_min(T& relaxWhat, const T& relaxBy) {
    relaxWhat = std::min( relaxWhat, relaxBy );
}
