#include <Solvers/pch.h>
#include "algo/Relax.hpp"

using namespace std;

class Solver598E
{
public:
    void run();

    void sort(int& p, int& q)
    {
        if (p < q) swap(p, q);
    }
};

void Solver598E::run()
{
    int veryBigPrice = 30 * 30 * 60;
    vector<vector<vector<int>>> minPrice(31, vector<vector<int>>(31, vector<int>(51, veryBigPrice)));
    for (int a = 1; a <= 30; ++a)
        for (int b = 1; b <= a; ++b)
        {
            minPrice[a][b][0] = 0;
            if (a * b <= 50)
                minPrice[a][b][a * b] = 0;
            int verticalPrice = b * b;
            int horizontalPrice = a * a;
            for (int d = 1; d <= 50; ++d)
                for (int d1 = 0; d1 <= d; ++d1)
                {
                    int d2 = d - d1;
                    for (int verticalCutPos = 1; verticalCutPos < a; ++verticalCutPos)
                    {
                        auto h1 = b;
                        auto w1 = verticalCutPos;
                        sort(h1, w1);
                        auto h2 = b;
                        auto w2 = a - verticalCutPos;
                        sort(h2, w2);
                        relaxMin(minPrice[a][b][d], verticalPrice + minPrice[h1][w1][d1] + minPrice[h2][w2][d2]);
                    }

                    for (int horizontalCutPos = 1; horizontalCutPos < b; ++horizontalCutPos)
                    {
                        auto h1 = horizontalCutPos;
                        auto w1 = a;
                        sort(h1, w1);
                        auto h2 = b - horizontalCutPos;
                        auto w2 = a;
                        sort(h2, w2);
                        relaxMin(minPrice[a][b][d], horizontalPrice + minPrice[h1][w1][d1] + minPrice[h2][w2][d2]);
                    }
                }
        }


    int nTests;
    cin >> nTests;
    for (int i = 0; i < nTests; ++i)
    {
        int a, b, d;
        cin >> a >> b >> d;
        sort(a, b);
        cout << minPrice[a][b][d] << "\n";
    }

}

class Solver598ETest : public ProblemTest {};

TEST_F(Solver598ETest, Example1)
{
    string input = R"(4
2 2 1
2 2 3
2 2 2
2 2 4
)";
    string output = R"(5
5
4
0
)";
    setInput(input);
    Solver598E().run();
    EXPECT_EQ(output, getOutput());
}


