#pragma once
#include <array>
#include <numeric>

template<typename T, size_t n>
class GeomVector
{
public:
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

template<typename T, int n>
GeomVector<T, n> operator+(const GeomVector<T, n>& a, const GeomVector<T, n>& b)
{
	auto res = a;
	res += b;
	return res;
}

template<typename T, int n>
GeomVector<T, n> operator-(const GeomVector<T, n>& a, const GeomVector<T, n>& b)
{
	auto res = a;
	res -= b;
	return res;
}

template<typename T, int n>
GeomVector<T, n> operator*(const GeomVector<T, n>& a, const T& b)
{
	auto res = a;
	res *= b;
	return res;
}

template<typename T, int n>
GeomVector<T, n> operator*(const T& a, const GeomVector<T, n>& b)
{
	auto res = b;
	res *= a;
	return res;
}

template<typename T, int n>
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

template<typename T>
using GeomVector2 = GeomVector<T, 2>;
using GeomVector2I = GeomVector2<int>;

template<typename T>
T det(const GeomVector2<T>& a, const GeomVector2<T>& b)
{
	return a[0] * b[1] - a[1] * b[0];
}