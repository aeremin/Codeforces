#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/io/printvector.h"
using namespace std;

class Solver668A {
public:
    void run();
};

void Solver668A::run() {
    int n, m, q;
    cin >> n >> m >> q;
    
    struct Query { int a, b, c, d; };
    deque<Query> queries;

    for (int i : range(q)) {
        int a, b;
        cin >> a >> b;
        int c = 1;
        int d = 0;
        if (a == 3)
            cin >> c >> d;
        queries.push_front({ a, b - 1, c - 1, d });
    }

    vector<vector<int>> field(n, vector<int>(m));
    for (auto q : queries) {
        if (q.a == 1) {
            auto t = field[q.b][m - 1];
            for (int i = m - 1; i > 0; --i)
                field[q.b][i] = field[q.b][i - 1];
            field[q.b][0] = t;
        }

        if (q.a == 2) {
            auto t = field[n - 1][q.b];
            for (int i = n - 1; i > 0; --i)
                field[i][q.b] = field[i - 1][q.b];
            field[0][q.b] = t;
        }
        if (q.a == 3) {
            field[q.b][q.c] = q.d;
        }
    }

    for (auto& line : field) {
        printVector(line);
        print('\n');
    }
}


class Solver668ATest : public ProblemTest {};


TEST_F(Solver668ATest, Example1) {
    string input = R"(2 2 6
2 1
2 2
3 1 1 1
3 2 2 2
3 1 2 8
3 2 1 8
)";
    string output = R"(8 2
1 8
)";
    setInput(input);
    Solver668A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}
TEST_F(Solver668ATest, Example2) {
    string input = R"(3 3 2
1 2
3 2 2 5
)";
    string output = R"(0 0 0
0 0 5
0 0 0
)";
    setInput(input);
    Solver668A().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}
