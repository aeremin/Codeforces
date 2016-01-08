#pragma once
#include <array>
#include <numeric>
#include <cstdint>

template<typename T, size_t n>
class GeomVector
{
public:
    GeomVector()
    {
        comps_ = std::array<T, n>{};
    }

    GeomVector(const std::array<T, n>& from) : comps_(from) {}

	T& operator[](size_t ind) { return comps_[ind]; }
	const T& operator[](size_t ind) const { return comps_[ind]; }
	
	bool operator==(const GeomVector& other) const { return comps_ == other.comps_; }
	
	T lengthSquared() const	
	{
		return std::accumulate(begin(comps_), end(comps_), T(), [](const T& a, const T& b) {
			return a + b * b;
		});
	}
	
	const GeomVector& operator+=(const GeomVector& other)
	{
		for (int i = 0; i < n; ++i)
			comps_[i] += other.comps_[i];
		return *this;
	}

	const GeomVector& operator-=(const GeomVector& other)
	{
		for (int i = 0; i < n; ++i)
			comps_[i] -= other.comps_[i];
		return *this;
	}

	const GeomVector& operator*=(const T& multiplier)
	{
		for (int i = 0; i < n; ++i)
			comps_[i] *= multiplier;
		return *this;
	}

private:
	std::array<T, n> comps_;
};

template<typename T, size_t n>
GeomVector<T, n> operator+(const GeomVector<T, n>& a, const GeomVector<T, n>& b)
{
	auto res = a;
	res += b;
	return res;
}

template<typename T, size_t n>
GeomVector<T, n> operator-(const GeomVector<T, n>& a, const GeomVector<T, n>& b)
{
	auto res = a;
	res -= b;
	return res;
}

template<typename T, size_t n>
GeomVector<T, n> operator*(const GeomVector<T, n>& a, const T& b)
{
	auto res = a;
	res *= b;
	return res;
}

template<typename T, size_t n>
GeomVector<T, n> operator*(const T& a, const GeomVector<T, n>& b)
{
	auto res = b;
	res *= a;
	return res;
}

template<typename T, size_t n>
bool operator<(const GeomVector<T, n>& a, const GeomVector<T, n>& b)
{
	for (int i = 0; i < n; ++i)
	{
		if (a[i] < b[i])
			return true;
		else if (a[i] > b[i])
			return false;
	}
	return false;
}

template<class T, size_t n>
T dot(const GeomVector<T, n>& a, const GeomVector<T, n>& b)
{
    T res{};
    for (int i = 0; i < n; ++i)
        res += a[i] * b[i];
    return res;
}


template<typename T>
using GeomVector2 = GeomVector<T, 2>;
using GeomVector2I = GeomVector2<int>;
using GeomVector2I64 = GeomVector2<int64_t>;
using GeomVector2F = GeomVector2<float>;

template<typename T>
T det(const GeomVector2<T>& a, const GeomVector2<T>& b)
{
	return a[0] * b[1] - a[1] * b[0];
}