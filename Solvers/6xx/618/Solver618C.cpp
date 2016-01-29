#include <Solvers/pch.h>
#include "algo/geometry/geomvector.hpp"
#include "algo/algebra/Sign.hpp"

using namespace std;

class Solver618C
{
public:
    void run();
};

void Solver618C::run()
{
    int n;
    cin >> n;
    vector<GeomVector2I64> stars(n);
    for (auto& s : stars)
        cin >> s[0] >> s[1];

    vector<int> smallestTri = { 0, 1 };
    for (int i = 2; i < n; ++i)
    {
        if (det(stars[i] - stars[0], stars[1] - stars[0]) != 0)
        {
            smallestTri.push_back(i);
            break;
        }
    }

    int valueToSkip = smallestTri.back();
    for (int i = 2; i < n; ++i)
    {
        if (i == valueToSkip)
            continue;
        vector<int64_t> signs;
        GeomVector2I64 currP = stars[i];
        for (int j = 0; j < 3; ++j)
        {
            int64_t s1 = det(stars[smallestTri[j]] - stars[smallestTri[(j + 1) % 3]],
                             stars[smallestTri[(j + 2) % 3]] - stars[smallestTri[(j + 1) % 3]]);
            int64_t s2 = det(currP - stars[smallestTri[(j + 1) % 3]],
                             stars[smallestTri[(j + 2) % 3]] - stars[smallestTri[(j + 1) % 3]]);

            signs.push_back(s2 * sgn(s1));
        }

        bool nonStrictlyInside = true;
        int opInd = 0;
        for (int j = 0; j < 3; ++j)
        {
            nonStrictlyInside = nonStrictlyInside && signs[j] >= 0;
            if (signs[j] == 0)
                opInd = (j + 1) % 3;
        }

        if (!nonStrictlyInside)
            continue;

        smallestTri[opInd] = i;
    }

    cout << (smallestTri[0] + 1) << " " << (smallestTri[1] + 1) << " " << (smallestTri[2] + 1);
}

class Solver618CTest : public ProblemTest {};

TEST_F(Solver618CTest, Example1)
{
    setInput("3             0 1             1 0             1 1");
    Solver618C().run();
    EXPECT_EQ("1 2 3", getOutput());
}

TEST_F(Solver618CTest, Example2)
{
    setInput("5             0 0             0 2             2 0             2 2             1 1");
    Solver618C().run();
    EXPECT_EQ("1 5 3", getOutput());
}