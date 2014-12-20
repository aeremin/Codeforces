#include <iostream>
#include <vector>
#include <deque>
#include <set>
#include <cassert>
#include <algorithm>

using namespace std;

template<class T, int N>
class GeomVector
{
public:
	GeomVector()
	{
		for (int i = 0; i < N; ++i) data_[i] = 0;
	}

	T& operator[](int ind) { return data_[ind]; }
	const T& operator[](int ind) const { return data_[ind]; }

private:
	T data_[N];
};

template<class T, int N>
T dot(const GeomVector<T, N>& a, const GeomVector<T, N>& b)
{
	T res = 0;
	for (int i = 0; i < N; ++i) res += a[i] * b[i];
	return res;
}

template<class T, int N>
GeomVector<T, N> operator+(const GeomVector<T, N>& a, const GeomVector<T, N>& b)
{
	GeomVector<T, N> result;
	for (int i = 0; i < N; ++i)
	{
		result[i] = a[i] + b[i];
	}
	return result;
}

template<class T, int N>
GeomVector<T, N> operator-(const GeomVector<T, N>& a, const GeomVector<T, N>& b)
{
	GeomVector<T, N> result;
	for (int i = 0; i < N; ++i)
	{
		result[i] = a[i] - b[i];
	}
	return result;
}

template<class T, int N>
GeomVector<T, N> operator*(double alpha, const GeomVector<T, N>& b)
{
	GeomVector<T, N> result;
	for (int i = 0; i < N; ++i)
	{
		result[i] = alpha * b[i];
	}
	return result;
}

typedef GeomVector<long long, 2> Vector2I;

bool isStrictlyInside(long long rSquared, const Vector2I& point)
{
	return dot(point, point) < rSquared;
}

bool isOnBorder(long long rSquared, const Vector2I& point)
{
	return dot(point, point) == rSquared;
}

bool isIntersecting(long long rSquared, const Vector2I& a, const Vector2I& b)
{
	bool aOnBorder = isOnBorder(rSquared, a);
	bool bOnBorder = isOnBorder(rSquared, b);
	if (aOnBorder || bOnBorder) return true;

	bool aIn = isStrictlyInside(rSquared, a);
	bool bIn = isStrictlyInside(rSquared, b);
	
	if (aIn != bIn) return true;
	if (aIn && bIn) return false;

	long long a11 = dot(a, a);
	long long a12 = -dot(a, b - a);
	long long a22 = dot(b - a, b - a);
    return (a11 * a22 - a12 * a12 <= a22 * rSquared) && a12 >= 0 && a22 >= a12;
}


int main()
{
#ifndef ONLINE_JUDGE  
	freopen("input.txt", "rt", stdin);
	freopen("output.txt", "wt", stdout);
#endif

	Vector2I p;
	cin >> p[0] >> p[1];
	int nA;
	cin >> nA;
	vector<Vector2I> a(nA);
	for (int i = 0; i < nA; ++i) cin >> a[i][0] >> a[i][1];
	a.push_back(a.front());

	Vector2I q;
	cin >> q[0] >> q[1];
	int nB;
	cin >> nB;
	vector<Vector2I> b(nB);
	for (int i = 0; i < nB; ++i) cin >> b[i][0] >> b[i][1];
	b.push_back(b.front());

	int rSquared = dot(p - q, p - q);
	
	for (int iA = 0; iA < nA; ++iA)
	{
		auto& curA = a[iA];
		for (int iB = 0; iB < nB; ++iB)
		{
			auto& curB1 = b[iB];
			auto& curB2 = b[iB + 1];
			if (isIntersecting(rSquared, curB1 - q - curA + p, curB2 - q - curA + p))
			{
				cout << "YES";
				return 0;
			}
		}
	}

	for (int iB = 0; iB < nB; ++iB)
	{
		auto& curB = b[iB];
		for (int iA = 0; iA < nA; ++iA)
		{
			auto& curA1 = a[iA];
			auto& curA2 = a[iA + 1];
			if (isIntersecting(rSquared, curA1 - p - curB + q, curA2 - p - curB + q))
			{
				cout << "YES";
				return 0;
			}
		}
	}

	cout << "NO";
	return 0;
}