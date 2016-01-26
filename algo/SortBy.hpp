#pragma once
#include <vector>

template<typename T, class WeightFunctor>
void sortBy(std::vector<T>& toSort, WeightFunctor weightFunctor)
{
	auto weightCompare = [&](const T& a, const T& b) {return weightFunctor(a) < weightFunctor(b); };
	std::sort(begin(toSort), end(toSort), weightCompare);
}