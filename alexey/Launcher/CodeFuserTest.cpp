#include <gtest/gtest.h>
#include "CodeFuser.h"

TEST(CodeFuserTest, GetProblemNameFromGtestFilterNoMatch)
{
    EXPECT_EQ(GetProblemNameFromGtestFilter("--gtest_filter=*CodeFuserTest*"), "");
    EXPECT_EQ(GetProblemNameFromGtestFilter("--gtest_filter=*Factorial*"), "");
    EXPECT_EQ(GetProblemNameFromGtestFilter("--gtest_filter=*1091*"), "");
    EXPECT_EQ(GetProblemNameFromGtestFilter("--gtest_filter=*867*"), "");
    EXPECT_EQ(GetProblemNameFromGtestFilter("--gtest_filter=*FBHC*"), "");
    EXPECT_EQ(GetProblemNameFromGtestFilter("--gtest_filter=*FBHC1"), "");
}

TEST(CodeFuserTest, GetProblemNameFromGtestFilterMatch3)
{
    EXPECT_EQ(GetProblemNameFromGtestFilter("--gtest_filter=*863A*"), "863A");
    EXPECT_EQ(GetProblemNameFromGtestFilter("--gtest_filter=*123J*"), "123J");
}

TEST(CodeFuserTest, GetProblemNameFromGtestFilterMatch4)
{
    EXPECT_EQ(GetProblemNameFromGtestFilter("--gtest_filter=*1063A*"), "1063A");
    EXPECT_EQ(GetProblemNameFromGtestFilter("--gtest_filter=*1234J*"), "1234J");
}

TEST(CodeFuserTest, GetProblemNameFromGtestFilterFBHC)
{
    EXPECT_EQ(GetProblemNameFromGtestFilter("--gtest_filter=*FBHC3D*"), "FBHC3D");
}

TEST(CodeFuserTest, GetSolverFileNameByProblemName3)
{
    EXPECT_EQ(GetSolverFileNameByProblemName("863A"), "Solvers/8xx/863/Solver863A.cpp");
}

TEST(CodeFuserTest, GetSolverFileNameByProblemName4)
{
    EXPECT_EQ(GetSolverFileNameByProblemName("1063A"), "Solvers/10xx/1063/Solver1063A.cpp");
}

TEST(CodeFuserTest, GetSolverFileNameByProblemNameFBHC)
{
    EXPECT_EQ(GetSolverFileNameByProblemName("FBHC3D"), "Solvers/FBHC/Round3/SolverFBHC3D.cpp");
}