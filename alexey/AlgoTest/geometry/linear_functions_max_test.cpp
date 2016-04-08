#include <gtest/gtest.h>
#include "algo/geometry/linear_functions_max.h"
#include "iter/range.h"
#include "util/relax.h"

TEST( LinearFunctionsMaximumTest, DefaultConstructedIsEmpty ) {
    LinearFunctionsMaximum<double> lfm;
    EXPECT_TRUE( lfm.is_empty() );
}

TEST( LinearFunctionsMaximumTest, OneFunction ) {
    LinearFunctionsMaximum<double> lfm;
    lfm.add_function( 1.0, 2.0 ); // y = x + 2
    EXPECT_FALSE( lfm.is_empty() );
    for ( double x = 0.0; x < 10.0; x += 1.0 )
    EXPECT_DOUBLE_EQ( x + 2, lfm.get_value( x ) );
}

TEST( LinearFunctionsMaximumTest, TwoFunctions ) {
    LinearFunctionsMaximum<double> lfm;
    lfm.add_function( 1.0, 2.0 ); // y = x + 2
    lfm.add_function( 2.0, 1.0 ); // y = 2x + 1
    EXPECT_DOUBLE_EQ( 0, lfm.get_value( -2 ) );
    EXPECT_DOUBLE_EQ( 1, lfm.get_value( -1 ) );
    EXPECT_DOUBLE_EQ( 2, lfm.get_value( 0 ) );
    EXPECT_DOUBLE_EQ( 3, lfm.get_value( 1 ) );
    EXPECT_DOUBLE_EQ( 5, lfm.get_value( 2 ) );
    EXPECT_DOUBLE_EQ( 7, lfm.get_value( 3 ) );
}

TEST( LinearFunctionsMaximumTest, AddingNotImportantFunction ) {
    LinearFunctionsMaximum<int> lfm;
    lfm.add_function( 1, 3 ); // y = x + 3
    lfm.add_function( 3, 1 ); // y = 3x + 1
    lfm.add_function( 2, 2 );
    EXPECT_DOUBLE_EQ( 1, lfm.get_value( -2 ) );
    EXPECT_DOUBLE_EQ( 2, lfm.get_value( -1 ) );
    EXPECT_DOUBLE_EQ( 3, lfm.get_value( 0 ) );
    EXPECT_DOUBLE_EQ( 4, lfm.get_value( 1 ) );
    EXPECT_DOUBLE_EQ( 7, lfm.get_value( 2 ) );
    EXPECT_DOUBLE_EQ( 10, lfm.get_value( 3 ) );
}

TEST( LinearFunctionsMaximumTest, NotPreciseIntersection ) {
    LinearFunctionsMaximum<int> lfm;
    lfm.add_function( 1, 3 ); // y = x + 3
    lfm.add_function( 3, 0 ); // y = 3x
    // Second function is strictly bigger starting from x = 2
    EXPECT_DOUBLE_EQ( 2, lfm.get_value( -1 ) );
    EXPECT_DOUBLE_EQ( 3, lfm.get_value( 0 ) );
    EXPECT_DOUBLE_EQ( 4, lfm.get_value( 1 ) );
    EXPECT_DOUBLE_EQ( 6, lfm.get_value( 2 ) );
    EXPECT_DOUBLE_EQ( 9, lfm.get_value( 3 ) );
}

TEST(LinearFunctionsMaximumTest, SameSlope) {
    LinearFunctionsMaximum<int> lfm;
    lfm.add_function(1, 4); // y = x + 3
    lfm.add_function(1, 3); // y = x + 4
    EXPECT_DOUBLE_EQ(3, lfm.get_value(-1));
    EXPECT_DOUBLE_EQ(4, lfm.get_value(0));
    EXPECT_DOUBLE_EQ(5, lfm.get_value(1));
    EXPECT_DOUBLE_EQ(6, lfm.get_value(2));
    EXPECT_DOUBLE_EQ(7, lfm.get_value(3));
}

TEST(LinearFunctionsMaximumTest, SameSlope2) {
    LinearFunctionsMaximum<int> lfm;
    lfm.add_function(1, 3); // y = x + 4
    lfm.add_function(1, 4); // y = x + 3
    EXPECT_DOUBLE_EQ(3, lfm.get_value(-1));
    EXPECT_DOUBLE_EQ(4, lfm.get_value(0));
    EXPECT_DOUBLE_EQ(5, lfm.get_value(1));
    EXPECT_DOUBLE_EQ(6, lfm.get_value(2));
    EXPECT_DOUBLE_EQ(7, lfm.get_value(3));
}

TEST(LinearFunctionsMaximumTest, SameFunction) {
    LinearFunctionsMaximum<int> lfm;
    lfm.add_function(1, 4); // y = x + 4
    lfm.add_function(1, 4); // y = x + 4
    EXPECT_DOUBLE_EQ(3, lfm.get_value(-1));
    EXPECT_DOUBLE_EQ(4, lfm.get_value(0));
    EXPECT_DOUBLE_EQ(5, lfm.get_value(1));
    EXPECT_DOUBLE_EQ(6, lfm.get_value(2));
    EXPECT_DOUBLE_EQ(7, lfm.get_value(3));
}

TEST( LinearFunctionsMaximumTest, RandomizedTestComparedWithBruteForce ) {
    const int nFunctions = 100;
    const int maxCoeff = 10000;
    std::vector<std::pair<int, int>> functions;
    LinearFunctionsMaximum<int> lfm;
    for ( auto i : range(nFunctions) ) {
        std::pair<int, int> fn = { std::rand() % ( 2 * maxCoeff ) - maxCoeff, std::rand() % ( 2 * maxCoeff ) - maxCoeff };
        lfm.add_function( fn.first, fn.second );
        functions.push_back( fn );
        
        for ( int x : range( -1000, 1000 ) ) {
            auto bruteForceValue = std::numeric_limits<int>::min();
            for ( auto fn : functions )
                relax_max( bruteForceValue, fn.first * x + fn.second );
            ASSERT_EQ( bruteForceValue, lfm.get_value( x ) );
        }
    }
}