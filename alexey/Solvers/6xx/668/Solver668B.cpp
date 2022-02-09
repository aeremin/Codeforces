#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
#include "algo/io/printvector.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/668/problem/B
class Solver668B {
public:
    void run();

    void rotate(vector<int>& v, int64_t a) {
        int64_t n = v.size();
        a = a % n;
        a += n;
        a = a % n;
        if (a == 0)
            return;
        vector<char> rotated(n, false);
        for (auto i : range(n)) {
            if (rotated[i])
                continue;
            auto t = v[i];
            int prev = (i - a + n) % n;
            int curr = i;
            do {
                v[curr] = v[prev];
                rotated[curr] = true;
                curr = prev;
                prev = (curr - a + n) % n;
            } while (prev != i);
            v[curr] = t;
            rotated[curr] = true;
        }
    }
   
    int64_t fixedModDiv(int64_t a, int64_t b) {
        auto res = a % b;
        res += b;
        res = res % b;
        return (a - res) / b;
    }
};

void Solver668B::run() {
    int n, q;
    cin >> n >> q;
    vector<pair<int, int64_t>> queries = { { 1, 0 } };
    for (int i : range(q)) {
        int t = read<int>();
        if (t == 1) {
            int s = read<int>();
            if (queries.back().first == 1)
                queries.back().second += s;
            else
                queries.push_back({ 1, s });

            if (queries.size() > 1) {
                queries.front().second += 2 * fixedModDiv(queries.back().second, 2);
                if (queries.back().second % 2 == 0)
                    queries.pop_back();
                else
                    queries.back().second = 1;
            }
        }
        else {
            if (queries.back().first == 2)
                queries.pop_back();
            else
                queries.push_back({ 2, 0 });
        }
    }

    vector<int> positions(n);
    iota(begin(positions), end(positions), 1);

    int k = count(begin(queries), end(queries), make_pair( 2, int64_t(0) ));

    rotate(positions, queries.front().second);

    vector<int> oddPositions, evenPositions;
    for (int i : range(n / 2)) {
        evenPositions.push_back(positions[2 * i]);
        oddPositions.push_back(positions[2 * i + 1]);
    }

    rotate(evenPositions, k);

    for (int i : range(n / 2)) {
        positions[2 * i] = evenPositions[i];
        positions[2 * i + 1] = oddPositions[i];
    }

    if (queries.back().first == 2)
        rotate(positions, -1);

    for (auto p : positions) {
        print(p);
        print(' ');
    }
}


class Solver668BTest : public ProblemTest {};

TEST_F(Solver668BTest, Rotate) {
    vector<int> a = { 1, 2, 3, 4, 5, 6 };
    Solver668B().rotate(a, -2);
    vector<int> b = { 3, 4, 5, 6, 1, 2 };
    EXPECT_EQ(a, b);
}

TEST_F(Solver668BTest, Rotate2) {
    vector<int> a = { 1, 2, 3, 4, 5, 6 };
    Solver668B().rotate(a, -666);
    vector<int> b = { 1, 2, 3, 4, 5, 6 };
    EXPECT_EQ(a, b);
}

TEST_F(Solver668BTest, Rotate3) {
    vector<int> a = { 1, 2, 3, 4, 5, 6 };
    Solver668B().rotate(a, 666);
    vector<int> b = { 1, 2, 3, 4, 5, 6 };
    EXPECT_EQ(a, b);
}


TEST_F(Solver668BTest, Example1) {
    string input = R"(6 3
1 2
2
1 2
)";
    string output = R"(4 3 6 5 2 1 
)";
    setInput(input);
    Solver668B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver668BTest, Example2) {
    string input = R"(2 3
1 1
2
1 -2
)";
    string output = R"(1 2 
)";
    setInput(input);
    Solver668B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver668BTest, Example3) {
    string input = R"(4 2
2
1 3
)";
    string output = R"(1 4 3 2 
)";
    setInput(input);
    Solver668B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}
