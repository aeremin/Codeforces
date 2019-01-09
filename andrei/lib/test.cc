#include "std.h"

#include <gtest/gtest.h>

#include "graph/graph.h"
#include "graph/topological_sort.h"
#include "graph/distance_unweighted.h"
#include "io/scan.h"
#include "io/print.h"
#include "io/targets.h"
#include "util/lexicographical_compare.h"
#include "util/hash.h"


struct Simple {
  int value;
};

struct Foo2 {
  int bar;
  string buz;
};

struct Foo4 {
  int a;
  unsigned b;
  string c;
  Foo2 d;
};

struct ExplicitPair {
  explicit ExplicitPair(int a__, double b__) : a(a__), b(b__) {}
  int a;
  double b;
};

class Fancy {
public:
  const std::string value() const { return value_; }

private:
  std::string value_;
};

using IntPair = pair<int, int>;

DEFINE_HASH_1(Fancy, value());
DEFINE_HASH_1(Simple, value);
DEFINE_HASH_2(Foo2, bar, buz);
DEFINE_HASH_2(IntPair, first, second);
DEFINE_HASH_4(Foo4, a, b, c, d);



int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  // TODO: set library_tests__enable_checks from command line flags, add launch script
  // TODO: runs tests without -DLOCAL_PC
  return RUN_ALL_TESTS();


  // TODO: make all these unit tests

  print_ln(1.0);
  print_ln(1000.0);
  print_ln(1, ' ', 2);

  set_io_file_names(foo_in_foo_out("test"));

//   std::unordered_set<pair<int, int>> int_pair_uset;
//   int_pair_uset.insert({13, 17});
//   std::unordered_set<Foo2> my_uset;
//   my_uset.insert({});

  auto k = scan<int>();
  printf("%d", k);

  int n = scan();
  vector<pair<int, double>> v;
  for (int i = 0; i < n; ++i) {
    v.push_back(SCAN_2());
  }
  pair<int, double> p;
  scan(p.first, p.second);
  pair<int, double> pp = SCAN_2();
  v.push_back(p);
  v.push_back(pp);
  vector<ExplicitPair> w;
  w.push_back(ExplicitPair SCAN_2());
  ExplicitPair ep SCAN_2();

  auto vec = scan_vector_2<pair<int, double>>(n);
  string str = scan();

  auto www = value_or(v, 7);
  std::map<int, int> m;
  auto mmm = value_or(m, 7);
  FIX_UNUSED(www);
  FIX_UNUSED(mmm);


  return 0;
}
