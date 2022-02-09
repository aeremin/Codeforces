#include <Solvers/pch.h>
#include "algo/geometry/geomvector.h"

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/497/problem/D
class Solver497D
{
public:
    void run();
    
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
};

void Solver497D::run()
{
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
                return;
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
                return;
            }
        }
    }

    cout << "NO";

}

class Solver497DTest : public ProblemTest
{
};

TEST_F( Solver497DTest, Example1 )
{
    setInput(
R"(
1 0
4
0 0
1 0
1 5
0 5

9 0
4
9 0
9 -5
10 -5
10 0
)");
    Solver497D().run();
    EXPECT_EQ("YES", getOutput());
}

TEST_F( Solver497DTest, Example2 )
{
    setInput(
R"(
0 0
3
1 0
2 -1
2 1

0 0
3
-1 0
-2 1
-2 -1
)");
    Solver497D().run();
    EXPECT_EQ("NO", getOutput());
}