#pragma once
#include <vector>
#include "util/weight_comparator.h"

template<typename T, class WeightFunctor>
void sortBy(std::vector<T>& toSort, WeightFunctor weightFunctor)
{
	std::sort(begin(toSort), end(toSort), make_weight_comparator(weightFunctor));
}