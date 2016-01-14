#pragma once
#include <cstdint>

template<typename T>
T factorial(T one, uint64_t n)
{
	auto res = one;
	for (uint64_t i = 1; i <= n; ++i)
		res *= i;
	return res;
}

