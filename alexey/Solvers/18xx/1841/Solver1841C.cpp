
#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
#include "algo/segment_tree/segment_tree.h"
#include "algo/segment_tree/update_appliers/update_applier.h"
#include "algo/segment_tree/update_types/set_to.h"
#include "util/relax.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1841/problem/C

class Solver1841C {
  public:
    void run();
};

struct Counts {
  array<int, 5> positive = {0, 0, 0, 0, 0};
  array<int, 5> negative = {0, 0, 0, 0, 0};
};

Counts from_char(char c) {
  Counts r;
  r.positive[c - 'A']++;
  return r;
}

struct Concatenate {
  Counts operator()(const Counts& l, const Counts& r) const {
    array<int, 6> r_summed = {0, 0, 0, 0, 0, 0};
    for (int j = 4; j >= 0; --j) {
      r_summed[j] = r.positive[j] + r.negative[j] + r_summed[j + 1];
    }

    Counts res;
    for (int j : range(5)) {
      res.negative[j] = r.negative[j] + l.negative[j];
      res.positive[j] = r.positive[j];
      if (r_summed[j + 1] > 0) {
        res.negative[j] += l.positive[j];
      } else {
        res.positive[j] += l.positive[j];
      }
    }

    return res;
  }
};

template <>
struct UpdateApplier<update_types::SetTo<Counts>, Concatenate> {
    static Counts apply(const Counts& v, const update_types::SetTo<Counts>& upd, size_t length) {
        if (upd.isId_) {
          return v;
        }

        Counts res;
        for (int j : range(5)) {
          res.positive[j] = length * upd.value_.positive[j];
          res.negative[j] = length * upd.value_.negative[j];
        }

        return res;
    }
};

int64_t Value(const Counts& c) {
  int64_t digits[] = {1, 10, 100, 1000, 10000};
  int64_t res = 0;
  for (int j : range(5)) {
    auto d = digits[j];
    res += d * (c.positive[j] - c.negative[j]);
  }
  return res;
}

void Solver1841C::run() {
  for (int k : range(read<int>())) {
    auto s = read<string>();
    auto sk = s;
    vector<Counts> data(s.length());
    for (int i : range(s.length())) {
      data[i] = from_char(s[i]);
    }
    auto segmentTree = makeSegmentTree(data, Concatenate(), update_types::SetTo<Counts>());

    int64_t answer = numeric_limits<int64_t>::min();
    for (int i : range(s.length())) {
      for (char c : {'A', 'B', 'C', 'D', 'E'}) {
        sk[i] = c;
        segmentTree.updateElement(i, update_types::SetTo<Counts>(from_char(c)));
        relax_max(answer, Value(segmentTree.getValueOnSegment(0, s.length())));
      }
      sk[i] = s[i];
      segmentTree.updateElement(i, update_types::SetTo<Counts>(from_char(s[i])));
    }

    print(answer);
    print("\n");
  }
}


class Solver1841CTest : public ProblemTest {};

TEST_F(Solver1841CTest, Example1) {
    setInput(R"(4
DAAABDCA
AB
ABCDEEDCBA
DDDDAAADDABECD
)");
    string output = R"(11088
10010
31000
15886

)";
    Solver1841C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


