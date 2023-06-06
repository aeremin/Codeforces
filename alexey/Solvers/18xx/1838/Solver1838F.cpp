
#include <Solvers/pch.h>

#include "algo/io/baseio.h"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1838/problem/F

class InteractiveSolver1838F {
public:
  void Run();
  virtual string GetResponse(/* TODO */);
  virtual void PrintAnswer(/* TODO */);
};

string InteractiveSolver1838F::GetResponse(/* TODO */) {
  cout << /*TODO << */ endl;
  return read<string>();
}

void InteractiveSolver1838F::PrintAnswer(/* TODO */) { cout << /* TODO << */ endl; }

void InteractiveSolver1838F::Run() {}

class Solver1838F {
public:
  void run();
};

void Solver1838F::run() { InteractiveSolver1838F().Run(); }


class Solver1838FTest : public ProblemTest {};

TEST_F(Solver1838FTest, DISABLED_Example1) {
  setInput(R"(
)");
  string output = R"(
? 2 2
>><
>>v
^<<

? 1 1
>><
>>v
^<<

! 1 2 ^
)";
  Solver1838F().run();
  EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1838FTest, DISABLED_Example2) {
  setInput(R"(
)");
  string output = R"(
? 2 2
v>v<
^v<v
v>v^
>v>v

! 3 3 >
)";
  Solver1838F().run();
  EXPECT_EQ_FUZZY(getOutput(), output);
}


class InteractiveSolver1838FForTest : public InteractiveSolver1838F {
public:
  InteractiveSolver1838FForTest() {}
  string GetResponse(/* TODO */) override;
  void PrintAnswer(/* TODO */) override;
};

string InteractiveSolver1838FForTest::GetResponse(/* TODO */) {
  // TODO
  return "";
}

void InteractiveSolver1838FForTest::PrintAnswer(/* TODO */) {
  // TODO
}

TEST(InteractiveSolver1838FTest, Example1) { InteractiveSolver1838FForTest().Run(); }
