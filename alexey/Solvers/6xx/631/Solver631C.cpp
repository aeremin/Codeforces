#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
#include "algo/io/readvector.h"
#include "util/relax.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/631/problem/C
class Solver631C
{
public:
    void run();
};

void Solver631C::run()
{
    int n = read<int>();
    int m = read<int>();
    auto startNumsIn = readVector<int>(n);
    vector<pair<int, int>> sortType(n, { 0, -1 });
    auto maxSortLen = 0;
    for (int i : range(m)) {
        int t, r;
        cin >> t >> r;
        relax_max(maxSortLen, r);
        sortType[r - 1] = { t, i };
    }
    
    deque<int> answer(begin(startNumsIn) + maxSortLen, end(startNumsIn));
    deque<int> sortedNums(begin(startNumsIn), begin(startNumsIn) + maxSortLen);
    sort(begin(sortedNums), end(sortedNums));

    pair<int, int> currSortType;
    for (int i : range(maxSortLen)) {
        if (i == 0)
            currSortType = sortType[maxSortLen - 1];
        else if (currSortType.second < sortType[maxSortLen - 1 - i].second)
            currSortType = sortType[maxSortLen - 1 - i];
        if (currSortType.first == 1) {
            answer.push_front(sortedNums.back());
            sortedNums.pop_back();
        }
        else {
            answer.push_front(sortedNums.front());
            sortedNums.pop_front();
        }
    }

    for (auto elt : answer)
        cout << elt << " ";
}

class Solver631CTest : public ProblemTest {};

TEST_F(Solver631CTest, Example1)
{
    string input = R"(3 1
1 2 3
2 2
)";
    string output = R"(2 1 3 )";
    setInput(input);
    Solver631C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver631CTest, Example2)
{
    string input = R"(4 2
1 2 4 3
2 3
1 2
)";
    string output = R"(2 4 1 3 )";
    setInput(input);
    Solver631C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


