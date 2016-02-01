#pragma once
#include <vector>
#include "algo/WeightComparator.hpp"

template<typename T, class WeightFunctor>
void sortBy(std::vector<T>& toSort, WeightFunctor weightFunctor)
{
	std::sort(begin(toSort), end(toSort), makeWeightComparator(weightFunctor));
}