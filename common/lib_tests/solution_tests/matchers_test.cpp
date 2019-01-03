#include "solution_tests/matchers.h"

using namespace testing;


TEST(MatchersTest, EqualsTrimmedMatches) {
  EXPECT_THAT("1", EqualsTrimmed("1"));
  EXPECT_THAT("\n1", EqualsTrimmed("1"));
  EXPECT_THAT("1\n", EqualsTrimmed("1"));
  EXPECT_THAT("1", EqualsTrimmed("\n1"));
  EXPECT_THAT("1", EqualsTrimmed("1\n"));
  EXPECT_THAT("   \n1\t\t  \n", EqualsTrimmed(" 1\n\n"));
}

TEST(MatchersTest, EqualsTrimmedNotMatches) {
  EXPECT_THAT("1", Not(EqualsTrimmed("2")));
  EXPECT_THAT("\n1", Not(EqualsTrimmed("2")));
  EXPECT_THAT("1\n", Not(EqualsTrimmed("2")));
  EXPECT_THAT("1", Not(EqualsTrimmed("\n2")));
  EXPECT_THAT("1", Not(EqualsTrimmed("2\n")));
  EXPECT_THAT("   \n1\t\t  \n", Not(EqualsTrimmed(" 2\n\n")));
}

TEST(MatchersTest, EqualsTrimmedGlider) {
  std::string glider(".X.\n..X\nXXX");
  EXPECT_THAT(glider, EqualsTrimmed(R"(
.X.
..X
XXX
  )"));
}

TEST(MatchersTest, EqualsFuzzy) {
  EXPECT_THAT("1  2\n3 ", EqualsFuzzy("1  2\n3 "));
  EXPECT_THAT("1  2\n3 ", Not(EqualsFuzzy("1   2\n3 ")));
  EXPECT_THAT("1  2\n3 ", Not(EqualsFuzzy("1  3\n3 ")));
  EXPECT_THAT("1  2\n3 ", Not(EqualsFuzzy("1  2\n3 4 ")));
  EXPECT_THAT("1  2\n3", Not(EqualsFuzzy("1  2\n4")));

  EXPECT_THAT("1  2.\n3 ", EqualsFuzzy("1  2.00000001\n3 "));

  EXPECT_THAT("1000000000", Not(EqualsFuzzy("1000000001")));
  EXPECT_THAT("1000000000.0", EqualsFuzzy("1000000001.0"));
}
