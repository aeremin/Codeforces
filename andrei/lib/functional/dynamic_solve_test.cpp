#include "functional/dynamic_solve.h"

#include "util/hash.h"

#include <algorithm>

#include <gmock/gmock.h>
#include <gtest/gtest.h>


TEST(DynamicSolveTest, Fibonacci) {
  using Solver = DynamicSolver<int(int)>;
  Solver fibonacci_solver([](Solver& solver, int x) {
    return (x <= 2) ? 1 : solver(x - 1) + solver(x - 2);
  });
  EXPECT_EQ(fibonacci_solver(6), 8);
}

TEST(DynamicSolveTest, LongestCommonSubsequence) {
  std::string a = "abbcccabca";
  std::string b = "abababac";
  using Solver = DynamicSolver<int(int, int)>;
  Solver lcs_solver([&](Solver& solver, int n, int m) {
    if (n < 0 || m < 0)
      return 0;
    if (a[n] == b[m])
      return solver(n - 1, m - 1) + 1;
    return std::max(solver(n - 1, m), solver(n, m - 1));
  });
  EXPECT_EQ(lcs_solver(a.size() - 1, b.size() - 1), 6);
}
