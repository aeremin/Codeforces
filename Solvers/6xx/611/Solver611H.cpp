#include <Solvers/pch.h>

using namespace std;

template<typename T>
class UnorderedPair
{
public:
    UnorderedPair(T a, T b) : a_(move(a)), b_(move(b)) {}

    bool operator==(const UnorderedPair<T>& other) const { return (a_ == other.a_ && b_ == other.b_) || (a_ == other.b_ && b_ == other.a_); }

    std::pair<T, T> rep() const { return{ a_, b_ }; }

private:
    T a_, b_;
};

namespace std
{
template<typename T>
struct hash<UnorderedPair<T>>
{
    size_t operator()(const UnorderedPair<T>& p) const { return hash<T>()(p.rep().first) ^ hash<T>()(p.rep().second);  }
};
}

class Solver611H
{
public:
    void run();

    int calculateBalance(const vector<unordered_set<int>>& verticesDecomposition,
        const unordered_map<UnorderedPair<size_t>, int> numEdges,
        const vector<size_t>& subset) const
    {
        int ans = 0;
        for (auto elt : subset)
            ans += verticesDecomposition[elt].size();

        for (auto elt1 : subset)
            for (auto elt2 : subset)
                if (elt1 <= elt2)
                    ans -= numEdges.at(UnorderedPair<size_t>(elt1, elt2));

        return ans;
    }

    pair<vector<unordered_set<int>>, unordered_map<UnorderedPair<size_t>, int>> filterByIndices(
        const vector<unordered_set<int>>& verticesDecomposition,
        const unordered_map<UnorderedPair<size_t>, int> numEdges, 
        const vector<size_t>& indices) const
    {
        vector<unordered_set<int>> verticesDecompositionFiltered;
        unordered_map<UnorderedPair<size_t>, int> numEdgesFiltered;
        vector<pair<int, int>> outFiltered;
        for (size_t i = 0; i < indices.size(); ++i)
            verticesDecompositionFiltered.push_back(verticesDecompositionFiltered[indices[i]]);

        for (size_t i = 0; i < indices.size(); ++i)
            for (size_t j = 0; j <= i; ++j)
                numEdgesFiltered[{i, j}] = numEdges.at({ indices[i], indices[j] });

        return{ move(verticesDecompositionFiltered), move(numEdgesFiltered) };
    }

    vector<size_t> fromBitMask(uint64_t bitmask) const
    {
        vector<size_t> result;
        uint64_t c = 0;
        while (bitmask > 0)
        {
            if (bitmask % 2 == 1)
                result.push_back(c);
            bitmask /= 2;
            ++c;
        }
        return result;
    }

    bool findAnswer(const vector<unordered_set<int>>& verticesDecomposition,
        unordered_map<UnorderedPair<size_t>, int> numEdges,
        vector<pair<int, int>>& out) const
    {
        vector<int> balances(1 << verticesDecomposition.size());
        for (size_t mask = 1; mask < balances.size(); ++mask)
        {
            balances[mask] = calculateBalance(verticesDecomposition, numEdges, fromBitMask(mask));
            if (balances[mask] < 1)
                return false;
        }

        for (size_t mask = balances.size() / 2; mask < balances.size(); ++mask)
        {
            if (balances[mask] == 1)
            {
                auto indices = fromBitMask(mask);
                auto filteredStrictBalance = filterByIndices(verticesDecomposition, numEdges, indices);
                vector<pair<int, int>> outFiltered;
                bool res = findAnswer(filteredStrictBalance.first, filteredStrictBalance.second, outFiltered);
                if (!res)
                    return false;

                auto antiIndices = fromBitMask(balances.size() - 1 - mask);
                auto cutOfStrictBalance = filterByIndices(verticesDecomposition, numEdges, indices);

                cutOfStrictBalance.first.push_back({ -1 });
                /*for (auto i : antiIndices)
                    for (auto j : indices)
                        cutOfStrictBalance.second[{i, cutOfStrictBalance.first.size() - 1}] += numEdges.at({ i, j });*/

                vector<pair<int, int>> outCut;
                res = findAnswer(cutOfStrictBalance.first, cutOfStrictBalance.second, outCut);
                if (!res)
                    return false;

                out = outFiltered;
                for (auto e : outCut)
                {
                    if (e.first < e.second) swap(e.first, e.second);
                    if (e.second == -1)
                    {
                        for (size_t iComponent = 0; iComponent < verticesDecomposition.size(); ++iComponent)
                        {
                            if (verticesDecomposition[iComponent].count(e.first))
                            {
                                for (auto i : indices)
                                {
                                    if (numEdges.at({ iComponent, i }) > 0)
                                    {
                                        --numEdges[{ iComponent, i }];
                                        e.second = *verticesDecomposition[iComponent].begin();
                                        break;
                                    }
                                }
                                break;
                            }
                        }
                    }
                    out.push_back(e);
                    return true;
                }
            }
        }
    }
};

void Solver611H::run()
{

}

class Solver611HTest : public ProblemTest
{
};

TEST_F( Solver611HTest, Example1 )
{
    setInput("");
    Solver611H().run();
    EXPECT_EQ("", getOutput());
}

TEST_F( Solver611HTest, Example2 )
{
    setInput("");
    Solver611H().run();
    EXPECT_EQ("", getOutput());
}