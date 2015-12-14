#pragma once
#include <array>
#include <numeric>

template<typename T, int n>
class GeomVector
{
public:
	GeomVector(const std::array<typename T, n>& from) : comps_(from) {}

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
GeomVector<typename T, n> operator+(const GeomVector<typename T, n>& a, const GeomVector<typename T, n>& b)
{
	auto res = a;
	res += b;
	return res;
}

template<typename T, int n>
GeomVector<typename T, n> operator-(const GeomVector<typename T, n>& a, const GeomVector<typename T, n>& b)
{
	auto res = a;
	res -= b;
	return res;
}

template<typename T, int n>
GeomVector<typename T, n> operator*(const GeomVector<typename T, n>& a, const typename T& b)
{
	auto res = a;
	res *= b;
	return res;
}

template<typename T, int n>
GeomVector<typename T, n> operator*(const typename T& a, const GeomVector<typename T, n>& b)
{
	auto res = b;
	res *= a;
	return res;
}

using GeomVector2I = GeomVector<int, 2>;