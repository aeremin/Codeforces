#pragma once
#include <cstdint>
#include <algorithm>

template<typename T>
T binomialCoefficient(T one, int64_t n, int64_t k)
{
	if (n < 0)
		return T(0);

	if (k >= n || k <= 0)
		return one;

	k = std::min(k, n - k);
	
	auto res = one;
	for (int64_t i = k - 1; i >= 0; --i)
		res = (res * (n - i)) / (k - i);

	return res;
}