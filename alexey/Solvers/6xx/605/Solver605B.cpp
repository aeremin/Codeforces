#include "Solvers/pch.h"
#include <limits>
#include "util/weight_comparator.h"

class Solver605B
{
public:
    void run();
};

struct EdgeInfo
{
    int64_t weight;
    int64_t originalIndex;
    int64_t from;
    int64_t to;
    int64_t isItMST;
};


void Solver605B::run()
{
    size_t nVertices, nEdges;
    cin >> nVertices >> nEdges;
    std::vector<EdgeInfo> allEdges(nEdges);
    for (size_t i = 0; i < nEdges; ++i)
    {
        cin >> allEdges[i].weight >> allEdges[i].isItMST;
        allEdges[i].originalIndex = i;
    }

    std::vector<EdgeInfo> mstEdges, nonMstEdges;
    std::copy_if(begin(allEdges), end(allEdges), std::back_inserter(mstEdges), [](const EdgeInfo& info){ return info.isItMST == 1; });
    std::copy_if(begin(allEdges), end(allEdges), std::back_inserter(nonMstEdges), [](const EdgeInfo& info){ return info.isItMST == 0; });
    
    if (mstEdges.size() != nVertices - 1)
    {
        std::cout << -1;
        return;
    }
    
    auto edgeWeight = [](const EdgeInfo& a){return a.weight; };
    std::sort(begin(mstEdges), end(mstEdges), make_weight_comparator(edgeWeight));
    std::sort(begin(nonMstEdges), end(nonMstEdges),  make_weight_comparator(edgeWeight));

    if (!nonMstEdges.empty())
    {
        bool canBeBuilt = true;
        for (int64_t i = 3; i <= nVertices; ++i)
        {
            int64_t jMin = (i - 2) * (i - 3) / 2;
            int64_t jMax = std::min<int64_t>((i - 2) * (i - 3) / 2 + i - 3, nonMstEdges.size() - 1);
            for (int64_t j = jMin; j <= jMax; ++j)
                canBeBuilt = canBeBuilt && mstEdges[i - 2].weight <= nonMstEdges[j].weight;
        }

        if (!canBeBuilt)
        {
            std::cout << -1;
            return;
        }
    }

    for (int64_t i = 2; i <= nVertices; ++i)
    {
        mstEdges[i - 2].from = 1;
        mstEdges[i - 2].to = i;
    }

    for (int64_t i = 2; i <= nVertices; ++i)
    {
        for (int64_t j = i + 1; j <= nVertices; ++j)
        {
            int64_t k = (j - 2) * (j - 3) / 2 + i - 2;
            if (k < nonMstEdges.size())
            {
                nonMstEdges[k].from = i;
                nonMstEdges[k].to = j;
            }
            else
                break;
        }
    }

    allEdges.clear();
    std::copy(begin(mstEdges), end(mstEdges), std::back_inserter(allEdges));
    std::copy(begin(nonMstEdges), end(nonMstEdges), std::back_inserter(allEdges));
    auto edgeCompareIndex = [](const EdgeInfo& a, const EdgeInfo& b){return a.originalIndex < b.originalIndex; };
    std::sort(begin(allEdges), end(allEdges), edgeCompareIndex);
    for (auto e : allEdges)
        cout << e.from << " " << e.to << "\n";
}

class Solver605BTest : public ProblemTest {};

TEST_F(Solver605BTest, Example1)
{
    setInput("3 3        1 0        2 1        3 1");
    Solver605B().run();
    EXPECT_EQ("-1", getOutput());
}

TEST_F(Solver605BTest, Example2)
{
    setInput("3 3        1 1        2 1        3 0");
    Solver605B().run();
    EXPECT_EQ("1 2\n1 3\n2 3\n", getOutput());
}

TEST_F(Solver605BTest, Example3)
{
    setInput("4 5        2 1        3 1        4 0        1 1        5 0");
    Solver605B().run();
    EXPECT_EQ("1 3\n1 4\n2 3\n1 2\n2 4\n", getOutput());
}

TEST_F(Solver605BTest, Example4)
{
    setInput("4 5        4 1        4 1        4 0        4 0        6 1");
    Solver605B().run();
    EXPECT_EQ("-1", getOutput());
}

TEST_F(Solver605BTest, Example5)
{
    setInput("3 2        3 1        2 1");
    Solver605B().run();
    EXPECT_EQ("1 3\n1 2\n", getOutput());
}

TEST_F(Solver605BTest, Example6)
{
    setInput("4 4        2 1        3 0        3 1        4 1");
    Solver605B().run();
    EXPECT_EQ("1 2\n2 3\n1 3\n1 4\n", getOutput());
}

TEST_F(Solver605BTest, Example7)
{
    setInput("4 4        2 1        3 0        3 1        4 1");
    Solver605B().run();
    EXPECT_EQ("1 2\n2 3\n1 3\n1 4\n", getOutput());
}
