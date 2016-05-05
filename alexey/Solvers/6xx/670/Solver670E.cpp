#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/io/readvector.hpp"
using namespace std;

class Solver670E {
public:
    void run();
};

void Solver670E::run() {
    int nSymbols, nOperations, startPosition;
    cin >> nSymbols >> nOperations >> startPosition;
    string startLine;
    cin >> startLine;
    list<char> line(begin(startLine), end(startLine));
    auto it = next(begin(line), startPosition - 1);

    unordered_map<char, int> toInt = { {'(', +1}, {')', -1} };

    string operations;
    cin >> operations;
    for (auto op : operations) {
        if (op == 'R')
            ++it;
        if (op == 'L')
            --it;
        if (op == 'D') {
            bool moveForward = (*it == '(');
            auto it2 = it;
            int balance = toInt[*it2];
            while (balance != 0) {
                if (moveForward)
                    ++it2;
                else
                    --it2;
                balance += toInt[*it2];
            }

            if (!moveForward)
                swap(it, it2);

            auto post = next(it2);
            line.erase(it, post);

            if (post == end(line))
                it = prev(post);
            else
                it = post;
        }
    }

    for (auto c : line)
        cout << c;
}


class Solver670ETest : public ProblemTest {};


TEST_F(Solver670ETest, Example1) {
    string input = R"(8 4 5
(())()()
RDLD
)";
    string output = R"(()
)";
    output.pop_back();
    setInput(input);
    Solver670E().run();
    EXPECT_EQ(output, getOutput());
}

TEST_F(Solver670ETest, Example2) {
    string input = R"(12 5 3
((()())(()))
RRDLD
)";
    string output = R"((()(()))
)";
    output.pop_back();
    setInput(input);
    Solver670E().run();
    EXPECT_EQ(output, getOutput());
}

TEST_F(Solver670ETest, Example3) {
    string input = R"(8 8 8
(())()()
LLLLLLDD
)";
    string output = R"(()()
)";
    output.pop_back();
    setInput(input);
    Solver670E().run();
    EXPECT_EQ(output, getOutput());
}

