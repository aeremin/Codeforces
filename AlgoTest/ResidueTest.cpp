#include <gtest/gtest.h>
#include "algo/Residue.hpp"
#include "algo/QuickPower.hpp"

using TestResidue = Residue<13>;

TEST( ResidueTest, CanConstructFromInt )
{
    TestResidue a = 27;
    EXPECT_EQ( 1, a.rep() );

    TestResidue b = -27;
    EXPECT_EQ( 12, b.rep() );
}

TEST( ResidueTest, CanCopy )
{
    TestResidue a = 27;
    TestResidue b;
    b = a;
    EXPECT_EQ( 1, b.rep() );
}


TEST( ResidueTest, CanAddInPlace )
{
    TestResidue a = 27;
    a += 22;
    EXPECT_EQ( 10, a.rep() );
}

TEST( ResidueTest, CanAdd )
{
    EXPECT_EQ( 2, ( TestResidue( 5 ) + 10 ).rep() );
    EXPECT_EQ( 2, ( TestResidue( 5 ) + TestResidue(10) ).rep() );
}

TEST( ResidueTest, CanSubstractInPlace )
{
    TestResidue a = 10;
    a -= 15;
    EXPECT_EQ( 8, a.rep() );
}

TEST( ResidueTest, CanSubstract )
{
    EXPECT_EQ( 8, ( TestResidue( 5 ) - 10 ).rep() );
    EXPECT_EQ( 8, ( TestResidue( 5 ) - TestResidue( 10 ) ).rep() );
}


TEST( ResidueTest, CanMultiplyOnPositiveInPlace )
{
    TestResidue a = 10;
    a *= -2;
    EXPECT_EQ( 6, a.rep() );
}

TEST( ResidueTest, CanMultiplyOnNegativeInPlace )
{
    TestResidue a = 10;
    a *= 2;
    EXPECT_EQ( 7, a.rep() );
}

TEST( ResidueTest, CanMultiply )
{
    EXPECT_EQ( 11, ( TestResidue( 5 ) * 10 ).rep() );
    EXPECT_EQ( 11, ( TestResidue( 5 ) * TestResidue( 10 ) ).rep() );
}

TEST( ResidueTest, CanIncrement )
{
    TestResidue a = 11;
    ++a;
    EXPECT_EQ( 12, a.rep() );
    a++;
    EXPECT_EQ( 0, a.rep() );
}

TEST( ResidueTest, CanDecrement )
{
    TestResidue a = 0;
    --a;
    EXPECT_EQ( 12, a.rep() );
    a--;
    EXPECT_EQ( 11, a.rep() );
}

TEST( ResidueTest, CanInverseAnyNonZeroResidueByPrimeModulo )
{
    const uint64_t prime = 867701;
    using PrimeResidue = Residue<prime>;
    for ( uint64_t i = 1; i < prime; ++i )
    {
        PrimeResidue r( i );
        PrimeResidue inv = r.inversed();
        PrimeResidue invTwice = inv.inversed();
        PrimeResidue product = r * inv;
        EXPECT_EQ( PrimeResidue( 1 ), product );
        EXPECT_EQ( r, invTwice );
    }
}


TEST( ResidueTest, CanOutputToStream )
{
    TestResidue a = 27;
    std::stringstream ss;
    ss << a;
    EXPECT_EQ( "1", ss.str() );
}

TEST( ResidueTest, FermatTheorem )
{
    const uint64_t prime = 867701;
    using PrimeResidue = Residue<prime>;
    for ( uint64_t i = 1; i < prime; ++i )
    {
        PrimeResidue r( i );
        auto res = quickPower( r, prime - 1 );
        EXPECT_EQ( PrimeResidue( 1 ), res );
    }
}