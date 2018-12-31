#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/io/readvector.hpp"
#include "math/sign.h"
using namespace std;

class Solver653C
{
public:
    void run();

    vector<int> seq;
    bool checkProperty(int i) {
        bool res = true;
        if (i > 0)
            res = res && (sgn(seq[i] - seq[i - 1]) == 2 * ((i) % 2) - 1);

        if (i < seq.size() - 1)
            res = res && (sgn(seq[i] - seq[i + 1]) == 2 * ((i) % 2) - 1);
        
        return res;
    }
};

void Solver653C::run()
{
    int n;
    cin >> n;
    seq = readVector<int>(n);
    vector<int> bads;
    for (int i : range(n))
        if (!checkProperty(i))
            bads.push_back(i);

    if (bads.size() > 6) {
        cout << 0;
        return;
    }

    set<pair<int, int>> goodSwaps;
    for (int b : bads)
        for (int c : range(n)){
            if (b == c) continue;
            swap(seq[b], seq[c]);
            {
                bool nowGood = true;
                for (auto bb : bads)
                    nowGood = nowGood && checkProperty(bb);

                for (auto bb : { b - 1, b + 1, c - 1, c, c + 1 })
                    nowGood = nowGood && (bb < 0 || bb >= n || checkProperty(bb));

                if (nowGood) goodSwaps.insert(minmax(b, c));
            }
            swap(seq[b], seq[c]);
        }

    cout << goodSwaps.size();
}

class Solver653CTest : public ProblemTest {};

TEST_F(Solver653CTest, Example1)
{
    string input = R"(5
2 8 4 7 7
)";
    string output = R"(2
)";
    output.pop_back();
    setInput(input);
    Solver653C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver653CTest, Example2)
{
    string input = R"(4
200 150 100 50
)";
    string output = R"(1
)";
    output.pop_back();
    setInput(input);
    Solver653C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver653CTest, Example3)
{
    string input = R"(10
3 2 1 4 1 4 1 4 1 4
)";
    string output = R"(8
)";
    output.pop_back();
    setInput(input);
    Solver653C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver653CTest, Example4)
{
    string input = R"(9
1 2 3 4 5 6 7 8 9
)";
    string output = R"(0
)";
    output.pop_back();
    setInput(input);
    Solver653C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


