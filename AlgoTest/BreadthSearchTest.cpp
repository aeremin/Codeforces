#include <gtest/gtest.h>
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
    SimpleGraph g( 7 );
    g.addEdge( 0, 1 );
    g.addEdge( 0, 2 );
    g.addEdge( 1, 3 );
    g.addEdge( 2, 3 );
    g.addEdge( 2, 6 );
    g.addEdge( 3, 4 );
    g.addEdge( 3, 5 );
    g.addEdge( 6, 5 );

    std::vector<size_t> expected = { 0, 1, 2, 3, 6, 4, 5 };
    std::vector<size_t> actual;
    auto processCbk = [&](size_t v) {actual.push_back(v);};
    breadthFirstSearch( g, processCbk, 0 );
    EXPECT_EQ( expected, actual );
}