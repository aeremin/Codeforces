#pragma once
#include <vector>
#include <iostream>

template<typename T>
void printVector(const std::vector<T>& out, std::string delimiter = " ")
{
    if (out.empty())
        return;
    for (size_t i = 0; i < out.size() - 1; ++i)
        std::cout << out[i] << delimiter;
    std::cout << out.back();
}
