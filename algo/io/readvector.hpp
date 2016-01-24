#pragma once
#include <vector>
#include <iostream>

template<typename T>
std::vector<T> readVector(size_t size)
{
    std::vector<T> res(size);
    for (auto& elt : res)
        std::cin >> elt;
    return res;
}