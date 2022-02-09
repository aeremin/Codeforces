
#include <Solvers/pch.h>

#include "algo/io/baseio.h"
#include "algo/io/readvector.h"
#include "iter/range.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1106/problem/B

class Solver1106B {
  public:
    void run();
};

void Solver1106B::run() {
    int n_dishes = read<int>();
    int n_clients = read<int>();
    auto available = readVector<int>(n_dishes);
    auto prices = readVector<int64_t>(n_dishes);
    map<pair<int64_t, int>, int> price_and_index_to_available;
    for (int i : range(n_dishes))
        price_and_index_to_available[{prices[i], i}] = available[i];

    for (int i_client : range(n_clients)) {
        int choice = read<int>() - 1;
        int amount = read<int>();
        int64_t total_bill = 0;

        while (amount) {
            if (price_and_index_to_available.empty()) {
                total_bill = 0;
                break;
            }

            auto it = price_and_index_to_available.find({prices[choice], choice});
            if (it == price_and_index_to_available.end())
                it = price_and_index_to_available.begin();
            int fullfillment = min(it->second, amount);
            total_bill += fullfillment * it->first.first;
            amount -= fullfillment;
            it->second -= fullfillment;
            if (it->second == 0)
                price_and_index_to_available.erase(it);
        }

        cout << total_bill << "\n";
    }
}


class Solver1106BTest : public ProblemTest {};

TEST_F(Solver1106BTest, Example1) {
    setInput(R"(
8 5
8 6 2 1 4 5 7 5
6 3 3 2 6 2 3 2
2 8
1 4
4 7
3 4
6 10

)");
    string output = R"(
22
24
14
10
39

)";
    Solver1106B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1106BTest, Example2) {
    setInput(R"(
6 6
6 6 6 6 6 6
6 66 666 6666 66666 666666
1 6
2 6
3 6
4 6
5 6
6 66

)");
    string output = R"(
36
396
3996
39996
399996
0

)";
    Solver1106B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1106BTest, Example3) {
    setInput(R"(
6 6
6 6 6 6 6 6
6 66 666 6666 66666 666666
1 6
2 13
3 6
4 11
5 6
6 6

)");
    string output = R"(
36
11058
99996
4333326
0
0

)";
    Solver1106B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}
