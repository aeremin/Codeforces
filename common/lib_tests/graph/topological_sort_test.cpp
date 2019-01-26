#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "graph/graph.h"
#include "graph/topological_sort_checked.h"
#include "graph/topological_sort_optimistic.h"

using testing::AnyOf;
using testing::ElementsAre;
using testing::Eq;

static void CheckOrder(const DirectedGraph<>& graph, const std::vector<int>& v) {
    for (size_t i = 0; i < v.size(); ++i) {
        for (size_t j = 0; j < i; ++j) ASSERT_TRUE(!graph.has_edge(v[i], v[j]));
    }
}

TEST(TopologicalSortTest, OneEdge) {
    DirectedGraph<> graph(2);
    graph.add_directed_edge(0, 1);
    {
        auto top_sorted_opt = topological_sort_reachable_optimistic(graph, {0});
        EXPECT_THAT(top_sorted_opt, ElementsAre(0, 1));
    }

    {
        auto top_sorted_checked = topological_sort_reachable_checked(graph, {0});
        ASSERT_EQ(top_sorted_checked.status(), TopologicalSortResult::Ok);
        EXPECT_THAT(top_sorted_checked.vertices(), ElementsAre(0, 1));
    }
}


TEST(TopologicalSortTest, Ok) {
    DirectedGraph<> graph(20);
    graph.add_directed_edge(0, 1);
    graph.add_directed_edge(0, 10);
    graph.add_directed_edge(0, 11);
    graph.add_directed_edge(1, 5);
    graph.add_directed_edge(5, 4);
    graph.add_directed_edge(5, 3);
    graph.add_directed_edge(3, 2);
    graph.add_directed_edge(4, 2);
    graph.add_directed_edge(12, 13);
    graph.add_directed_edge(13, 14);
    graph.add_directed_edge(14, 0);
    graph.add_directed_edge(14, 2);

    {
        auto top_sorted_opt = topological_sort_reachable_optimistic(graph, {0});
        CheckOrder(graph, top_sorted_opt);
    }
    {
        auto top_sorted_chk = topological_sort_reachable_checked(graph, {0});
        ASSERT_EQ(top_sorted_chk.status(), TopologicalSortResult::Ok);
        CheckOrder(graph, top_sorted_chk.vertices());
    }
}

TEST(TopologicalSortTest, Loop) {
    DirectedGraph<> graph2(20);

    graph2.add_directed_edge(0, 1);
    graph2.add_directed_edge(2, 3);
    graph2.add_directed_edge(4, 5);
    graph2.add_directed_edge(5, 4);  // bam!
    graph2.add_directed_edge(6, 7);
    graph2.add_directed_edge(8, 9);

    graph2.add_directed_edge(10, 0);   // bam!
    graph2.add_directed_edge(10, 4);   // bam!
    graph2.add_directed_edge(10, 11);  // bam!

    {
        auto top_sorted_chk = topological_sort_reachable_checked(graph2, {0, 2, 4, 6, 8});
        ASSERT_EQ(top_sorted_chk.status(), TopologicalSortResult::LoopDetected);
        EXPECT_THAT(top_sorted_chk.vertices(), ElementsAre(4, 5));
        EXPECT_THAT(top_sorted_chk.preloop(), ElementsAre());
        EXPECT_THAT(top_sorted_chk.loop(), ElementsAre(4, 5));
    }

    {
        auto top_sorted_chk = topological_sort_reachable_checked(graph2, {0, 2, 10, 6, 8});
        ASSERT_EQ(top_sorted_chk.status(), TopologicalSortResult::LoopDetected);
        EXPECT_THAT(top_sorted_chk.vertices(), ElementsAre(10, 4, 5));
        EXPECT_THAT(top_sorted_chk.preloop(), ElementsAre(10));
        EXPECT_THAT(top_sorted_chk.loop(), ElementsAre(4, 5));
    }

    {
        auto top_sorted_chk = topological_sort_reachable_checked(graph2, {0, 2, 5, 6, 8});
        ASSERT_EQ(top_sorted_chk.status(), TopologicalSortResult::LoopDetected);
        EXPECT_THAT(top_sorted_chk.vertices(), ElementsAre(5, 4));
        EXPECT_THAT(top_sorted_chk.preloop(), ElementsAre());
        EXPECT_THAT(top_sorted_chk.loop(), ElementsAre(5, 4));
    }

    {
        auto top_sorted_chk = topological_sort_reachable_checked(graph2, {5});
        ASSERT_EQ(top_sorted_chk.status(), TopologicalSortResult::LoopDetected);
        EXPECT_THAT(top_sorted_chk.vertices(), ElementsAre(5, 4));
        EXPECT_THAT(top_sorted_chk.preloop(), ElementsAre());
        EXPECT_THAT(top_sorted_chk.loop(), ElementsAre(5, 4));
    }

    {
        auto top_sorted_chk = topological_sort_reachable_checked(graph2, {10});
        ASSERT_EQ(top_sorted_chk.status(), TopologicalSortResult::LoopDetected);
        EXPECT_THAT(top_sorted_chk.vertices(), ElementsAre(10, 4, 5));
        EXPECT_THAT(top_sorted_chk.preloop(), ElementsAre(10));
        EXPECT_THAT(top_sorted_chk.loop(), ElementsAre(4, 5));
    }
}

//                   3
//             ______|_____
//            v            v
//            1            0
//         ___|___         |
//        v       v        |
//        2       6        v
//                |        5
//                v
//                4
//
TEST(TopologicalSortTest, Tree) {
    DirectedGraph<> graph(7);

    graph.add_directed_edge(3, 1);
    graph.add_directed_edge(3, 1);
    graph.add_directed_edge(1, 2);
    graph.add_directed_edge(1, 6);
    graph.add_directed_edge(6, 4);
    graph.add_directed_edge(3, 0);
    graph.add_directed_edge(0, 5);

    {
        auto v = topological_sort_reachable_optimistic(graph, {3});
        EXPECT_EQ(v.size(), 7);
        EXPECT_EQ(v[0], 3);
        EXPECT_THAT(v[1], AnyOf(Eq(0), Eq(1)));
    }
    {
        auto top_sorted_chk = topological_sort_reachable_checked(graph, {3});
        ASSERT_EQ(top_sorted_chk.status(), TopologicalSortResult::Ok);
        const auto& v = top_sorted_chk.vertices();
        EXPECT_EQ(v.size(), 7);
        EXPECT_EQ(v[0], 3);
        EXPECT_THAT(v[1], AnyOf(Eq(0), Eq(1)));
    }
}

class TopologicalSorterRandomTest : public testing::Test {
  public:
    static void SetUpTestCase() { graph = createRandomDAG(); }

    static void TearDownTestCase() { graph.reset(); }

    static std::unique_ptr<DirectedGraph<>> createRandomDAG() {
        std::vector<int> order(nVertices);
        std::iota(begin(order), end(order), 0);

        std::random_device rng;
        std::mt19937 urng(rng());
        std::shuffle(begin(order), end(order), urng);

        std::unique_ptr<DirectedGraph<>> result(new DirectedGraph<>(nVertices));
        for ([[maybe_unused]] auto i : range(nEdges)) {
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

TEST_F(TopologicalSorterRandomTest, TopologySort) {
    auto res = topological_sort_checked(*graph);
    EXPECT_EQ(res.status(), TopologicalSortResult::Ok);
}

TEST_F(TopologicalSorterRandomTest, TopologySortOptimistic) { auto res = topological_sort_optimistic(*graph); }

class TopologicalSorterLinearGraphTest : public testing::Test {
  public:
    static void SetUpTestCase() {
        graph = new DirectedGraph<>(nEdges + 1);
        for (auto i : range(nEdges))
            graph->add_directed_edge(i, i + 1);
    }

    static void TearDownTestCase() { delete graph; }

  protected:
    static DirectedGraph<>* graph;
    static const int nEdges = 2000000;
};

DirectedGraph<>* TopologicalSorterLinearGraphTest::graph = nullptr;

TEST_F(TopologicalSorterLinearGraphTest, TopologySort) {
    auto res = topological_sort_checked(*graph);
    EXPECT_EQ(res.status(), TopologicalSortResult::Ok);
}

TEST_F(TopologicalSorterLinearGraphTest, TopologySortOptimistic) { auto res = topological_sort_optimistic(*graph); }
