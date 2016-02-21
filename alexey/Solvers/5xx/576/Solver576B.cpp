#include <Solvers/pch.h>
#include "algo/io/readvector.hpp"
#include "algo/SortBy.hpp"

using namespace std;

class Solver576B
{
public:
    void run();
};

void Solver576B::run()
{
    int n;
    cin >> n;
    auto perm = readVector<int>(n);
    for (auto& elt : perm) 
        --elt;
    vector<vector<int>> cycles;
    for (int i = 0; i < n; ++i)
    {
        if (perm[i] == -1)
            continue;
        cycles.push_back({});
        int ii = i;
        while (perm[ii] != -1)
        {
            auto prev = ii;
            ii = perm[ii];
            perm[prev] = -1;
            cycles.back().push_back(ii);
        }
    }

    sortBy(cycles, [](const vector<int>& v) { return v.size(); });
    bool allCyclesAreEven = all_of(begin(cycles), end(cycles), [](const vector<int>& v) { return v.size() % 2 == 0; });
    
    if (cycles.front().size() == 1)
    {
        cout << "YES\n";
        auto root = cycles.front().front() + 1;
        for (size_t i = 1; i < cycles.size(); ++i)
            for (auto elt : cycles[i])
                cout << root << " " << (elt + 1) << "\n";
    }
    else if (cycles.front().size() == 2 && allCyclesAreEven)
    {
        cout << "YES\n";
        auto root1 = cycles.front()[0] + 1;
        auto root2 = cycles.front()[1] + 1;
        cout << root1 << " " << root2 << "\n";
        for (int i = 1; i < cycles.size(); ++i)
        {
            for (int j = 0; j < cycles[i].size(); j += 2)
            {
                cout << root1 << " " << (cycles[i][j + 0] + 1) << "\n";
                cout << root2 << " " << (cycles[i][j + 1] + 1) << "\n";
            }
        }
    }
    else
    {
        cout << "NO";
    }
}

class Solver576BTest : public ProblemTest {};

TEST_F(Solver576BTest, Example1)
{
    string input = R"(4
4 3 2 1
)";
    string output = R"(YES
4 1
4 3
1 2
)";
    setInput(input);
    Solver576B().run();
    EXPECT_EQ(output, getOutput());
}


TEST_F(Solver576BTest, Example2)
{
    string input = R"(3
3 1 2
)";
    string output = R"(NO
)";
    output.pop_back();
    setInput(input);
    Solver576B().run();
    EXPECT_EQ(output, getOutput());
}

TEST_F(Solver576BTest, Example3)
{
    string input = R"(2
1 2
)";
    string output = R"(YES
1 2
)";
    setInput(input);
    Solver576B().run();
    EXPECT_EQ(output, getOutput());
}

TEST_F(Solver576BTest, Example4)
{
    string input = R"(2
2 1
)";
    string output = R"(YES
2 1
)";
    setInput(input);
    Solver576B().run();
    EXPECT_EQ(output, getOutput());
}

