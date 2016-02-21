#pragma once
#include <cstdint>

template<class T>
T quickPower(const T& a, int64_t d, T one = T(1))
{
    auto res = one;
	auto m = a;
	while (d > 0)
	{
		if (d % 2 == 0)
		{
			m = m * m;
			d /= 2;
		}
		else
		{
			res *= m;
			d--;
		}
    }
	return res;
}