#include <gtest/gtest.h>

#include <memory>
#include <numeric>
#include <random>

#include "graph/graph.h"
#include "iter/range.h"
#include "algo/graph/TopologicalSorter.hpp"
#include "graph/topological_sort_checked.h"
#include "graph/topological_sort_optimistic.h"


class TopologicalSorterRandomTest : public testing::Test
{
public:
    static void SetUpTestCase()
    {
        graph = createRandomDAG();
    }

    static void TearDownTestCase()
    {
        graph.reset();
    }

    static std::unique_ptr<DirectedGraph<>> createRandomDAG()
    {
        std::vector<int> order(nVertices);
        std::iota(begin(order), end(order), 0);

        std::random_device rng;
        std::mt19937 urng(rng());
        std::shuffle(begin(order), end(order), urng);

        std::unique_ptr<DirectedGraph<>> result(new DirectedGraph<>(nVertices));
        for (auto i : range(nEdges))
        {
            int from = rand() % nVertices;
            int to = rand() % nVertices;
            if (order[to] < order[from])
                result->add_directed_edge(to, from);
            else if (order[to] > order[from])
                result->add_directed_edge(from, to);
        }

        return result;
    }

protected:
    static std::unique_ptr<DirectedGraph<>> graph;
    static const int nVertices = 10000;
    static const int nEdges = 5000000;
};

std::unique_ptr<DirectedGraph<>> TopologicalSorterRandomTest::graph = nullptr;

TEST_F( TopologicalSorterRandomTest, AndreyTopologySort )
{
    auto res = topological_sort_checked( *graph );
    EXPECT_EQ( res.status(), TopologicalSortResult::Ok );
}

TEST_F( TopologicalSorterRandomTest, AndreyTopologySortOptimistic )
{
    auto res = topological_sort_optimistic( *graph );
}

TEST_F( TopologicalSorterRandomTest, AlexeyTopologySort )
{
    auto ts = makeTopologicalSorter( *graph );
    EXPECT_TRUE(ts.isDAG());
}

/////////////////////////////////////////////////////////////////////////////////

class TopologicalSorterLinearGraphTest : public testing::Test
{
public:
    static void SetUpTestCase()
    {
        graph = new DirectedGraph<>( nEdges + 1 );
        for ( auto i : range( nEdges ) )
            graph->add_directed_edge( i, i + 1 );
    }

    static void TearDownTestCase()
    {
        delete graph;
    }

protected:
    static DirectedGraph<>* graph;
    static const int nEdges = 2000000;
};

DirectedGraph<>* TopologicalSorterLinearGraphTest::graph = nullptr;

TEST_F( TopologicalSorterLinearGraphTest, AndreyTopologySort )
{
    auto res = topological_sort_checked( *graph );
    EXPECT_EQ( res.status(), TopologicalSortResult::Ok );
}

TEST_F( TopologicalSorterLinearGraphTest, AndreyTopologySortOptimistic )
{
    auto res = topological_sort_optimistic( *graph );
}

// This test needs a lot of stack memory to succeed.
// If you see it failing, make sure to set Stack Reserve Size
// (codeforces project Properties -> Linker -> System -> Stack Reserve Size)
// to 256000000 (256mb, value used on Codeforces servers: https://codeforces.com/blog/entry/47003?#comment-313808)
TEST_F( TopologicalSorterLinearGraphTest, AlexeyTopologySort )
{
    auto ts = makeTopologicalSorter( *graph );
    EXPECT_TRUE( ts.isDAG() );
}

