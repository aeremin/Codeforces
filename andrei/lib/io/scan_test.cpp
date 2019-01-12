#include "io/scan.h"

#include <gmock/gmock.h>

#include "internal_tests/io_redirection.h"
#include "std.h"

using testing::ElementsAre;
using testing::Pair;


struct ExplicitPair {
  explicit ExplicitPair(int a__, double b__) : a(a__), b(b__) {}
  int a;
  double b;
};

using ScanTest = TestWithIORedirection;

TEST_F(ScanTest, Simple) {
  send_input("17");
  auto k = scan<int>();
  EXPECT_EQ(k, 17);
}

TEST_F(ScanTest, ScanN) {
  send_input(R"(
    180 3.14
  )");

  std::pair<int, double> x = SCAN_2();
  EXPECT_THAT(x, Pair(180, 3.14));
}

TEST_F(ScanTest, Vector) {
  send_input(R"(
3
0  .5
1 1.5
2 2.5
  )");

  int n = scan();
  auto v = scan_vector_2<pair<int, double>>(n);
  EXPECT_THAT(v, ElementsAre(Pair(0, 0.5), Pair(1, 1.5), Pair(2, 2.5)));
}

TEST_F(ScanTest, Explicit) {
  send_input(R"(
    1 0.2
  )");
  ExplicitPair p SCAN_2();
  EXPECT_EQ(p.a, 1);
  EXPECT_EQ(p.b, 0.2);
}
