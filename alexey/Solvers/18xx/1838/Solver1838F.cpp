
#include <Solvers/pch.h>

#include "algo/io/baseio.h"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1838/problem/F

struct Request {
  pair<int, int> start;
  pair<int, int> expected_finish;
  vector<vector<char>> dirs;
};

struct Response {
  bool looped;
  pair<int, int> end_location;
};

char Mirror(char c) {
  if (c == '<')
    return '>';
  if (c == '>')
    return '<';
  return c;
}


char Invert(char c) {
  if (c == '<')
    return '>';
  if (c == '>')
    return '<';
  if (c == 'v')
    return '^';
  return 'v';
}

Request Mirror(const Request& r) {
  int n = r.dirs.size();

  auto result = r;

  for (int x : range(n)) {
    for (int y : range(n)) {
      result.dirs[y][x] = Mirror(r.dirs[y][n - 1 - x]);
    }
  }

  result.start.first = n - 1 - r.start.first;
  result.expected_finish.first = n - 1 - r.expected_finish.first;
  return result;
}

Request Invert(const Request& r) {
  int n = r.dirs.size();

  auto result = r;

  for (int x : range(n)) {
    for (int y : range(n)) {
      result.dirs[y][x] = Invert(r.dirs[n - 1 - y][n - 1 - x]);
    }
  }

  result.start.first = n - 1 - r.start.first;
  result.start.second = n - 1 - r.start.second;
  result.expected_finish.first = n - 1 - r.expected_finish.first;
  result.expected_finish.second = n - 1 - r.expected_finish.second;
  return result;
}

Request LeftToRightRequest(int n, int lx, int rx, int ly, int ry) {
  Request r;
  r.dirs = vector<vector<char>>(n, vector<char>(n, ' '));
  r.start = {lx, ly};
  r.expected_finish = {n, ((rx - lx) % 2) ? ry - 1 : ly};

  for (int x : range(n)) {
    for (int y : range(ly)) {
      r.dirs[y][x] = '^';
    }

    for (int y : range(ry, n)) {
      r.dirs[y][x] = 'v';
    }
  }

  for (int y : range(ly, ry)) {
    for (int x : range(lx)) {
      r.dirs[y][x] = '<';
    }

    for (int x : range(rx, n)) {
      r.dirs[y][x] = '>';
    }
  }

  for (int x : range(lx, rx)) {
    for (int y : range(ly, ry)) {
      r.dirs[y][x] = ((x - lx) % 2) ? '^' : 'v';
    }
  }

  for (int x : range(lx, rx)) {
    r.dirs[((x - lx) % 2) ? ly : ry - 1][x] = '>';
  }

  return r;
}

Request RightToLeftRequest(int n, int lx, int rx, int ly, int ry) {
  return ((rx - lx) % 2) ? Invert(LeftToRightRequest(n, n - rx, n - lx, n - ry, n - ly))
                         : Mirror(LeftToRightRequest(n, n - rx, n - lx, ly, ry));
}

class InteractiveSolver1838F {
public:
  InteractiveSolver1838F(int n) : n_(n){};

  void Run();
  virtual Response GetResponse(const Request& r);
  virtual void PrintAnswer(pair<int, int> location, char dir);

private:
  void HandleUnexpectedBorderExit(pair<int, int> exit_location, int lx, int rx, int ly, int ry);

  int n_;
};

Response InteractiveSolver1838F::GetResponse(const Request& r) {
  cout << "? " << r.start.second + 1 << " " << r.start.first + 1 << "\n";
  for (const auto& l : r.dirs) {
    for (const auto c : l) {
      cout << c;
    }
    cout << "\n";
  }
  cout << endl;

  int x, y;
  cin >> y >> x;
  if (y == -1 && x == -1) {
    return {true, {0, 0}};
  } else {
    return {false, {x - 1, y - 1}};
  }
}

void InteractiveSolver1838F::PrintAnswer(pair<int, int> location, char dir) {
  cout << "! " << location.second + 1 << " " << location.first + 1 << " " << dir << endl;
}

void InteractiveSolver1838F::HandleUnexpectedBorderExit(pair<int, int> exit_location, int lx, int rx, int ly, int ry) {
  if (exit_location.first == -1) {
    PrintAnswer({lx, exit_location.second}, '<');
  } else if (exit_location.first == n_) {
    PrintAnswer({rx - 1, exit_location.second}, '>');
  } else if (exit_location.second == -1) {
    PrintAnswer({exit_location.first, ly}, '^');
  } else if (exit_location.second == n_) {
    PrintAnswer({exit_location.first, ry - 1}, 'v');
  }
}

void InteractiveSolver1838F::Run() {
  int ly = 0, ry = n_;

  while (ry - ly > 1) {
    auto my = (ry + ly) / 2;
    auto req1 = LeftToRightRequest(n_, 0, n_, ly, my);
    auto req2 = RightToLeftRequest(n_, 0, n_, ly, my);
    auto resp1 = GetResponse(req1);
    auto resp2 = GetResponse(req2);

    if (resp1.looped || resp2.looped) {
      ry = my;
    } else if (resp1.end_location == req1.expected_finish && resp2.end_location == req2.expected_finish) {
      ly = my;
    } else {
      auto border_end_location = (resp1.end_location == req1.expected_finish) ? resp2.end_location : resp1.end_location;
      HandleUnexpectedBorderExit(border_end_location, 0, n_, ly, my);
      return;
    }
  }

  int y = ly;
  auto req = LeftToRightRequest(n_, 0, n_, y, y + 1);
  auto resp = GetResponse(req);
  if (!resp.looped && resp.end_location != req.expected_finish) {
    HandleUnexpectedBorderExit(resp.end_location, 0, n_, y, y + 1);
    return;
  }

  bool need_left_to_right = resp.looped;
  int lx = 0, rx = n_;
  while (rx - lx > 1) {
    auto mx = (rx + lx) / 2;
    req = need_left_to_right ? LeftToRightRequest(n_, mx, rx, y, y + 1) : RightToLeftRequest(n_, lx, mx, y, y + 1);
    resp = GetResponse(req);
    if (need_left_to_right == (resp.looped || resp.end_location != req.expected_finish)) {
      lx = mx;
    } else {
      rx = mx;
    }
  }

  PrintAnswer({lx, y}, need_left_to_right ? '<' : '>');
}

class Solver1838F {
public:
  void run();
};

void Solver1838F::run() {
  int n;
  cin >> n;
  InteractiveSolver1838F(n).Run();
}


class Solver1838FTest : public ProblemTest {};

class InteractiveSolver1838FForTest : public InteractiveSolver1838F {
public:
  InteractiveSolver1838FForTest(int n, pair<int, int> location, char dir)
      : n_(n), location_(location), dir_(dir), InteractiveSolver1838F(n){};

  Response GetResponse(const Request& r) override;
  void PrintAnswer(pair<int, int> location, char dir) override;

  const int n_;
  const pair<int, int> location_;
  const char dir_;

  int number_of_guesses = 0;
  pair<int, int> guessed_location_;
  char guessed_dir_;
};

Response InteractiveSolver1838FForTest::GetResponse(const Request& r) {
  set<tuple<int, int>> visited;
  EXPECT_GE(r.start.first, 0);
  EXPECT_LT(r.start.first, n_);
  EXPECT_GE(r.start.second, 0);
  EXPECT_LT(r.start.second, n_);
  auto current_location = r.start;
  while (!visited.contains(current_location)) {
    visited.insert(current_location);
    auto current_dir = current_location == location_ ? dir_ : r.dirs[current_location.second][current_location.first];
    if (current_dir == '^')
      current_location.second--;
    if (current_dir == 'v')
      current_location.second++;
    if (current_dir == '<')
      current_location.first--;
    if (current_dir == '>')
      current_location.first++;

    if (current_location.first < 0 || current_location.first >= n_ || current_location.second < 0 ||
        current_location.second >= n_) {
      return {false, current_location};
    }
  }
  return {true, {0, 0}};
}

void InteractiveSolver1838FForTest::PrintAnswer(pair<int, int> location, char dir) {
  ++number_of_guesses;
  guessed_location_ = location;
  guessed_dir_ = dir;
}

TEST(InteractiveSolver1838FTest, Example1) {
  auto s = InteractiveSolver1838FForTest(11, {4, 8}, '^');
  s.Run();
  EXPECT_EQ(s.number_of_guesses, 1);
  EXPECT_EQ(s.location_, s.guessed_location_);
  EXPECT_EQ(s.dir_, s.guessed_dir_);
}

TEST(InteractiveSolver1838FTest, Example2) {
  auto s = InteractiveSolver1838FForTest(4, {3, 2}, 'v');
  s.Run();
  EXPECT_EQ(s.number_of_guesses, 1);
  EXPECT_EQ(s.location_, s.guessed_location_);
  EXPECT_EQ(s.dir_, s.guessed_dir_);
}

TEST(InteractiveSolver1838FTest, Example3) {
  auto s = InteractiveSolver1838FForTest(5, {0, 4}, '<');
  s.Run();
  EXPECT_EQ(s.number_of_guesses, 1);
  EXPECT_EQ(s.location_, s.guessed_location_);
  EXPECT_EQ(s.dir_, s.guessed_dir_);
}

TEST(InteractiveSolver1838FTest, Example4) {
  auto s = InteractiveSolver1838FForTest(3, {0, 2}, '>');
  s.Run();
  EXPECT_EQ(s.number_of_guesses, 1);
  EXPECT_EQ(s.location_, s.guessed_location_);
  EXPECT_EQ(s.dir_, s.guessed_dir_);
}

TEST(InteractiveSolver1838FTest, Example5) {
  auto s = InteractiveSolver1838FForTest(4, {3, 3}, '>');
  s.Run();
  EXPECT_EQ(s.number_of_guesses, 1);
  EXPECT_EQ(s.location_, s.guessed_location_);
  EXPECT_EQ(s.dir_, s.guessed_dir_);
}

TEST(InteractiveSolver1838FTest, Example6) {
  auto s = InteractiveSolver1838FForTest(6, {0, 0}, 'v');
  s.Run();
  ASSERT_EQ(s.number_of_guesses, 1);
  EXPECT_EQ(s.location_, s.guessed_location_);
  EXPECT_EQ(s.dir_, s.guessed_dir_);
}

TEST(InteractiveSolver1838FTest, ExampleMultipleEven) {
  int n = 10;
  for (int x : range(n)) {
    for (int y : range(n)) {
      for (char c : {'<', '>', 'v', '^'}) {
        auto s = InteractiveSolver1838FForTest(n, {x, y}, c);
        s.Run();
        ASSERT_EQ(s.number_of_guesses, 1);
        EXPECT_EQ(s.location_, s.guessed_location_) << x << " " << y << " " << c;
        EXPECT_EQ(s.dir_, s.guessed_dir_) << x << " " << y << " " << c;
      }
    }
  }
}

TEST(InteractiveSolver1838FTest, ExampleMultipleOdd) {
  int n = 13;
  for (int x : range(n)) {
    for (int y : range(n)) {
      for (char c : {'<', '>', 'v', '^'}) {
        auto s = InteractiveSolver1838FForTest(n, {x, y}, c);
        s.Run();
        ASSERT_EQ(s.number_of_guesses, 1);
        EXPECT_EQ(s.location_, s.guessed_location_) << x << " " << y << " " << c;
        EXPECT_EQ(s.dir_, s.guessed_dir_) << x << " " << y << " " << c;
      }
    }
  }
}


TEST(InteractiveSolver1838FTest, LeftToRightRequest) {
  auto r = LeftToRightRequest(4, 1, 4, 1, 3);
  EXPECT_EQ(r.start, make_pair(1, 1));
  EXPECT_EQ(r.expected_finish, make_pair(4, 2));
  EXPECT_EQ(r.dirs[0], vector<char>({'^', '^', '^', '^'}));
  EXPECT_EQ(r.dirs[1], vector<char>({'<', 'v', '>', 'v'}));
  EXPECT_EQ(r.dirs[2], vector<char>({'<', '>', '^', '>'}));
  EXPECT_EQ(r.dirs[3], vector<char>({'v', 'v', 'v', 'v'}));
}

TEST(InteractiveSolver1838FTest, RightToLeftRequest) {
  auto r = RightToLeftRequest(3, 0, 3, 2, 3);
  EXPECT_EQ(r.start, make_pair(2, 2));
  EXPECT_EQ(r.expected_finish, make_pair(-1, 2));
  EXPECT_EQ(r.dirs[0], vector<char>({'^', '^', '^'}));
  EXPECT_EQ(r.dirs[1], vector<char>({'^', '^', '^'}));
  EXPECT_EQ(r.dirs[2], vector<char>({'<', '<', '<'}));
}

TEST(InteractiveSolver1838FTest, LeftToRightRequestPartial) {
  auto r = LeftToRightRequest(3, 1, 3, 2, 3);
  EXPECT_EQ(r.start, make_pair(1, 2));
  EXPECT_EQ(r.expected_finish, make_pair(3, 2));
  EXPECT_EQ(r.dirs[0], vector<char>({'^', '^', '^'}));
  EXPECT_EQ(r.dirs[1], vector<char>({'^', '^', '^'}));
  EXPECT_EQ(r.dirs[2], vector<char>({'<', '>', '>'}));
}

TEST(InteractiveSolver1838FTest, RightToLeftRequestPartial) {
  auto r = RightToLeftRequest(3, 0, 2, 2, 3);
  EXPECT_EQ(r.start, make_pair(1, 2));
  EXPECT_EQ(r.expected_finish, make_pair(-1, 2));
  EXPECT_EQ(r.dirs[0], vector<char>({'^', '^', '^'}));
  EXPECT_EQ(r.dirs[1], vector<char>({'^', '^', '^'}));
  EXPECT_EQ(r.dirs[2], vector<char>({'<', '<', '>'}));
}
