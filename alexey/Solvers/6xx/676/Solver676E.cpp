#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/polynomial/polynomial.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/676/problem/E
class Solver676E {
public:
    void run();
};

bool isRoot(const Polynomial<int>& p, int x) {
    if (x == 0)
        return p.get_coefficient(0) == 0;

    int val = 0;
    for (int i : range(p.formal_degree() + 1)) {
        val += p.coefficient(i);
        if (val % x != 0)
            return false;
        val /= x;
    }

    return val == 0;
}

void Solver676E::run() {
    int n, k;
    cin >> n >> k;
    vector<bool> isKnown(n + 1);
    vector<int> coeffs(n + 1);
    string s;

    bool divisibleByX = false;
    int actionsMade = 0;

    for (int i : range(n + 1)) {
        cin >> s;
        isKnown[i] = (s != "?");
        actionsMade += isKnown[i];
        if (isKnown[i]) {
            stringstream ss(s);
            ss >> coeffs[i];
        }
        if (i == 0)
            divisibleByX = s == "0";
    }

    if (k == 0) {
        if (divisibleByX) {
            cout << "Yes";
        }
        else if (isKnown[0]) {
            cout << "No";
        }
        else if (actionsMade % 2 == 0) {
            cout << "No";
        }
        else cout << "Yes";
    }
    else {
        if (actionsMade == n + 1) {
            auto p = Polynomial<int>(move(coeffs));
            if (isRoot(p, k))
                cout << "Yes"; 
            else 
                cout << "No";
        }
        else {
            if ((n + 1) % 2 == 0)
                cout << "Yes";
            else
                cout << "No";
        }
    }

}


class Solver676ETest : public ProblemTest {};


TEST_F(Solver676ETest, Example1) {
    string input = R"(1 2
-1
?
)";
    string output = R"(Yes
)";
    setInput(input);
    Solver676E().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver676ETest, Example2) {
    string input = R"(2 100
-10000
0
1
)";
    string output = R"(Yes
)";
    setInput(input);
    Solver676E().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver676ETest, Example3) {
    string input = R"(4 5
?
1
?
1
?
)";
    string output = R"(No
)";
    setInput(input);
    Solver676E().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

