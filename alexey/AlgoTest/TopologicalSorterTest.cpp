#include <gtest/gtest.h>

#include <memory>
#include <numeric>

#include "algo/graph/Graph.hpp"
#include "iter/range.h"
#include "algo/graph/TopologicalSorter.hpp"
#include "graph/topological_sort.h"


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

    static std::unique_ptr<SimpleGraph> createRandomDAG()
    {
        std::vector<int> order(nVertices);
        std::iota(begin(order), end(order), 0);
        std::random_shuffle(begin(order), end(order));

        std::unique_ptr<SimpleGraph> result(new SimpleGraph(nVertices));
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
    static std::unique_ptr<SimpleGraph> graph;
    static const int nVertices = 10000;
    static const int nEdges = 50000000;
};

std::unique_ptr<SimpleGraph> TopologicalSorterRandomTest::graph = nullptr;

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
        graph = new SimpleGraph( nEdges + 1 );
        for ( auto i : range( nEdges ) )
            graph->add_directed_edge( i, i + 1 );
    }

    static void TearDownTestCase()
    {
        delete graph;
    }

protected:
    static SimpleGraph* graph;
    static const int nEdges = 2000000;
};

SimpleGraph* TopologicalSorterLinearGraphTest::graph = nullptr;

TEST_F( TopologicalSorterLinearGraphTest, AndreyTopologySort )
{
    auto res = topological_sort_checked( *graph );
    EXPECT_EQ( res.status(), TopologicalSortResult::Ok );
}

TEST_F( TopologicalSorterLinearGraphTest, AndreyTopologySortOptimistic )
{
    auto res = topological_sort_optimistic( *graph );
}

TEST_F( TopologicalSorterLinearGraphTest, DISABLED_AlexeyTopologySort )
{
    auto ts = makeTopologicalSorter( *graph );
    EXPECT_TRUE( ts.isDAG() );
}

