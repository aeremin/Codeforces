#include "Solvers/pch.h"

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/612/problem/E
class Solver612E
{
public:
    void run();

    typedef unordered_map<int64_t, vector<vector<int64_t>>> CycleDecomposition;
    
    CycleDecomposition decompose(vector<int64_t> permutation) const;
    vector<int64_t> compose(int64_t n, const CycleDecomposition& decomposed) const;
};

Solver612E::CycleDecomposition Solver612E::decompose(vector<int64_t> permutation) const
{
    CycleDecomposition result;
    for (int i = 0; i < permutation.size(); ++i)
    {
        if (permutation[i] == -1)
            continue;
        auto j = permutation[i];
        permutation[i] = -1;
        vector<int64_t> cycle = { i };
        while (j != i)
        {
            cycle.push_back(j);
            auto k = permutation[j];
            permutation[j] = -1;
            j = k;
        }
        result[cycle.size()].push_back(move(cycle));
    }
    return result;
}

vector<int64_t> Solver612E::compose(int64_t n, const CycleDecomposition& decomposed) const
{
    vector<int64_t> result(n);
    for (auto& p : decomposed)
        for (auto& cycle : p.second)
            for (int i = 0; i < cycle.size(); ++i)
                result[cycle[i]] = cycle[(i + 1) % cycle.size()];
    return result;
}

void Solver612E::run()
{
    int64_t n;
    cin >> n;
    vector<int64_t> permutation(n);
    for (auto& elt : permutation) { cin >> elt; elt--; }
    auto decomposed = decompose(move(permutation));
    bool canExtractRoot = true;
    CycleDecomposition rootDecomposition;
    for (auto& p : decomposed)
    {
        auto length = p.first;
        if (length % 2 == 1)
        {
            for (auto& cycle : p.second)
            {
                vector<int64_t> cycleRoot(length);
                for (int i = 0; i < length; ++i)
                    cycleRoot[i] = cycle[(i * (length + 1) / 2) % length];
                rootDecomposition[length].push_back(move(cycleRoot));
            }
        }
        else
        {
            if (p.second.size() % 2 == 0)
            {
                for (int i = 0; i < p.second.size(); i += 2)
                {
                    auto& cycle1 = p.second[i];
                    auto& cycle2 = p.second[i + 1];
                    vector<int64_t> cycleRoot(2 * length);
                    for (int i = 0; i < length; ++i)
                    {
                        cycleRoot[2 * i] = cycle1[i];
                        cycleRoot[2 * i + 1] = cycle2[i];
                    }
                    rootDecomposition[2 * length].push_back(move(cycleRoot));
                }
            }
            else
            {
                canExtractRoot = false;
                break;
            }
        }
    }

    if (!canExtractRoot)
    {
        cout << -1;
        return;
    }

    auto ans = compose(n, rootDecomposition);
    for (auto& elt : ans) cout << (elt + 1) << " ";
}

class Solver612ETest : public ProblemTest {};

TEST_F(Solver612ETest, Example1)
{
    setInput("4        2 1 4 3");
    Solver612E().run();
    EXPECT_EQ("3 4 2 1 ", getOutput());
}

TEST_F(Solver612ETest, Example2)
{
    setInput("4        2 1 3 4");
    Solver612E().run();
    EXPECT_EQ("-1", getOutput());
}

TEST_F(Solver612ETest, Example3)
{
    setInput("5        2 3 4 5 1");
    Solver612E().run();
    EXPECT_EQ("4 5 1 2 3 ", getOutput());
}