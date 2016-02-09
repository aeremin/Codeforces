#include "std.h"

#include "containers/indexer.h"
#include "graph/topological_sort.h"
#include "io/scan.h"
#include "io/targets.h"
#include "util/hash_compare.h"


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

DEFINE_COMPARISON_AND_HASH_1(Fancy, value());
DEFINE_COMPARISON_AND_HASH_1(Simple, value);
DEFINE_COMPARISON_AND_HASH_2(Foo2, bar, buz);
DEFINE_COMPARISON_AND_HASH_2(IntPair, first, second);
DEFINE_COMPARISON_AND_HASH_4(Foo4, a, b, c, d);

int main() {
  DirectedGraph_AdjacencyList graph(20);
  graph.add_edge(0, 1);
  graph.add_edge(0, 10);
  graph.add_edge(0, 11);
  graph.add_edge(1, 5);
  graph.add_edge(5, 4);
  graph.add_edge(5, 3);
  graph.add_edge(3, 2);
  graph.add_edge(4, 2);
  graph.add_edge(12, 13);
  graph.add_edge(13, 14);
  graph.add_edge(14, 0);
  graph.add_edge(14, 2);

  auto top_sorted_opt = topological_sort_reachable_optimistic(graph, {0});
  auto top_sorted_chk = topological_sort_reachable_checked(graph, {0});

  assert(top_sorted_chk.status == TopologicalSortResult::Ok);

  cout << "\ntop_sorted_opt:\n";
  for (auto vertex_index : top_sorted_opt)
    cout << vertex_index << " ";
  cout << "\n";
  cout << "\ntop_sorted_chk:\n";
  for (auto vertex_index : top_sorted_chk.vertices)
    cout << vertex_index << " ";
  cout << "\n";

  graph.add_edge(2, 1);  // bam!

  top_sorted_opt = topological_sort_reachable_optimistic(graph, {0});
  top_sorted_chk = topological_sort_reachable_checked(graph, {0});

  assert(top_sorted_chk.status == TopologicalSortResult::LoopDetected);

  cout << "\ntop_sorted_opt:\n";
  for (auto vertex_index : top_sorted_opt)
    cout << vertex_index << " ";
  cout << "\n";
  cout << "\ntop_sorted_chk:\n";
  for (auto vertex_index : top_sorted_chk.vertices)
    cout << vertex_index << " ";
  cout << "\n";

  cout << "\ndfs:\n";
  dfs(graph, {3, 7}, [](const DfsState&, GraphIndex vertex){
    cout << vertex << " ";
    return IterationControl::Continue;
  });
  cout << "\n";

  return 0;




  set_io_file_names(foo_in_foo_out("test"));

  std::set<pair<int, int>> int_pair_set;
  int_pair_set.insert({13, 17});
  std::unordered_set<pair<int, int>> int_pair_uset;
  int_pair_uset.insert({13, 17});
  std::set<Foo2> my_set;
  my_set.insert({});
  std::unordered_set<Foo2> my_uset;
  my_set.insert({});

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

  Indexer<std::string> indexer;
  int i_foo = indexer.insert_new("foo");
  int i_bar = indexer.insert_new("bar");
  assert(i_foo == indexer.index("foo"));
  assert("bar" == indexer.value(i_bar));
}
