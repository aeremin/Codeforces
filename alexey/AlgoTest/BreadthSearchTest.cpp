#include <gtest/gtest.h>
#include <algorithm>
#include "algo/graph/BreadthFirstSearch.hpp"

/*

         0
        / \
       1   2
      /   / \
     3 --    6
    / \     /
   4   5----

*/

TEST( BreadthFirstSearchTest, WorksOnSomeExample )
{
    UndirectedGraph<> g( 7 );
    g.add_edge( 0, 1 );
    g.add_edge( 0, 2 );
    g.add_edge( 1, 3 );
    g.add_edge( 2, 3 );
    g.add_edge( 2, 6 );
    g.add_edge( 3, 4 );
    g.add_edge( 3, 5 );
    g.add_edge( 6, 5 );

    std::vector<size_t> expected = { 0, 1, 2, 3, 6, 4, 5 };
    std::vector<size_t> actual;
    auto processCbk = [&](size_t v) {actual.push_back(v);};
    breadthFirstSearch( g, processCbk, 0 );
    // We don't know which one of 1/2, 3/6 and 4/5 will be visited first.
    std::sort(begin(actual) + 1, begin(actual) + 3);
    std::sort(begin(actual) + 3, begin(actual) + 5);
    std::sort(begin(actual) + 5, begin(actual) + 7);
    EXPECT_EQ( expected, actual );
}