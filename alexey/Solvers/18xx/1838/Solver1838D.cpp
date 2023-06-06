
#include <Solvers/pch.h>

#include "algo/io/baseio.h"
#include "algo/segment_tree/segment_tree.h"
#include "algo/segment_tree/update_appliers/set_to_idempotent.h"
#include "algo/segment_tree/update_types/set_to.h"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1838/problem/D

class Solver1838D {
public:
  void run();
};

enum class Coolness { Zero, Fail, Infinity };

struct JoinCoolness {
  Coolness operator()(const Coolness& l, const Coolness& r) const {
    if (l == Coolness::Fail)
      return Coolness::Fail;
    if (l == Coolness::Infinity)
      return Coolness::Infinity;

    return r;
  }
};

Coolness pairCoolness(char c1, char c2) {
  if (c1 == ')') {
    return Coolness::Fail;
  } else if (c2 == ')') {
    return Coolness::Zero;
  } else {
    return Coolness::Infinity;
  }
}

vector<Coolness> stringCoolness(const string& s) {
  vector<Coolness> result(s.size() / 2);
  for (int i : range(s.size() / 2)) {
    result[i] = pairCoolness(s[2 * i], s[2 * i + 1]);
  }
  return result;
}

char invert(char c) {
  if (c == '(')
    return ')';
  return '(';
}

void Solver1838D::run() {
  int n = read<int>();
  int q = read<int>();
  auto s = read<string>();
  auto antiS = s;
  for (int i : range(n)) {
    antiS[n - i - 1] = invert(s[i]);
  }

  if (n % 2 == 1) {
    for (int iq : range(q)) {
      print("NO\n");
    }
    return;
  }

  vector<Coolness> leftToRight = stringCoolness(s);
  vector<Coolness> rightToLeft = stringCoolness(antiS);

  auto stLeftToRight = makeSegmentTree(leftToRight, JoinCoolness(), update_types::SetTo<Coolness>());
  auto stRightToLeft = makeSegmentTree(rightToLeft, JoinCoolness(), update_types::SetTo<Coolness>());

  for (int iq : range(q)) {
    auto ind = read<int>() - 1;
    s[ind] = invert(s[ind]);

    auto antiInd = n - ind - 1;
    antiS[antiInd] = invert(antiS[antiInd]);

    stLeftToRight.updateElement(ind / 2, update_types::SetTo(pairCoolness(s[2 * (ind / 2)], s[2 * (ind / 2) + 1])));
    stRightToLeft.updateElement(
        antiInd / 2, update_types::SetTo(pairCoolness(antiS[2 * (antiInd / 2)], antiS[2 * (antiInd / 2) + 1])));

    if (stLeftToRight.getValueOnSegment(0, n / 2) == Coolness::Zero ||
        (stLeftToRight.getValueOnSegment(0, n / 2) == Coolness::Infinity &&
         stRightToLeft.getValueOnSegment(0, n / 2) == Coolness::Infinity)) {
      print("YES\n");
    } else {
      print("NO\n");
    }
  }
}


class Solver1838DTest : public ProblemTest {};

TEST_F(Solver1838DTest, Example1) {
  setInput(R"(10 9
(())()()))
9
7
2
6
3
6
7
4
8
)");
  string output = R"(YES
YES
NO
NO
YES
NO
YES
NO
NO

)";
  Solver1838D().run();
  EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1838DTest, Example2) {
  setInput(R"(3 2
(()
2
3
)");
  string output = R"(NO
NO

)";
  Solver1838D().run();
  EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1838DTest, Example3) {
  setInput(R"(3 2
(()
2
3
)");
  string output = R"(NO
NO

)";
  Solver1838D().run();
  EXPECT_EQ_FUZZY(getOutput(), output);
}
