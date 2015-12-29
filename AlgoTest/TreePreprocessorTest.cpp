#include <gtest/gtest.h>
#include "algo/TreePreprocessor.hpp"

int concatenate( int a, int b )
{
    return a + b;
}

using TreeCountingEdgesAndVertices = Graph<int, int>;

TEST( TreePreprocessorTest, ConcreteExample )
{
    TreeCountingEdgesAndVertices tree( 4, { 1, 1, 1, 1 } );
    tree.addEdge( 0, 1, 1 );
    tree.addEdge( 1, 2, 1 );
    tree.addEdge( 0, 3, 1 );
    
    TreePreprocessor<int, int> processor( tree );
    EXPECT_EQ( std::make_pair( 3, 4 ), processor.valueOnPath( 2, 3 ));
    for ( int i = 0; i < 4; ++i )
        EXPECT_EQ( std::make_pair( 0, 1 ), processor.valueOnPath( i, i ) );

    EXPECT_EQ( std::make_pair( 1, 2 ), processor.valueOnPath( 2, 1 ) );
    EXPECT_EQ( std::make_pair( 1, 2 ), processor.valueOnPath( 1, 2 ) );
}