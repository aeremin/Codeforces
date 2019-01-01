#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
using namespace std;

class Solver448E
{
public:
    void run();

    vector<int64_t> sortedDivisors(int64_t a) {
        vector<int64_t> res;
        vector<int64_t> big;
        for (int64_t d = 1; d * d <= a; ++d) {
            if (a % d == 0) {
                res.push_back(d);
                if (a != d * d) 
                    big.push_back(a / d);
            }
        }
        res.insert(res.end(),big.rbegin(), big.rend());
        return res;
    }

    vector<int64_t> xSortedDivisors;

    vector<int64_t> sortedDivisorDivisors(int64_t a) {
        vector<int64_t> res;
        for (auto c : xSortedDivisors) {
            if (c >= a) break;
            if (a % c == 0)
                res.push_back(c);
        }
        return res;
    }
};

void Solver448E::run()
{
    const int maxNeededSize = 100000;

    int64_t x, k;
    cin >> x >> k;
    xSortedDivisors = sortedDivisors(x);
    unordered_map<int64_t, vector<int64_t>> cachedDivisors;
    for (auto d : xSortedDivisors)
        cachedDivisors[d] = sortedDivisorDivisors(d);

    list<int64_t> s = { x };
    // Some compilers/STL implementations are stupid enough to have O(n) std::list::size implementation
    auto S = s.size();
    vector<list<int64_t>::iterator> notOnes;
    if (x > 1) 
        notOnes.push_back(begin(s));

    for (int64_t i : range(k)) {
        if (notOnes.empty())
            break;
        
        vector<list<int64_t>::iterator> notOnesNext;
        for (auto it : notOnes) {
            auto& divs = cachedDivisors[*it];
            auto itNew = s.insert(it, begin(divs), end(divs));
            S += divs.size();
            for (auto itNotOne = next(itNew); itNotOne != it; ++itNotOne)
                notOnesNext.push_back(itNotOne);
            notOnesNext.push_back(it);
        }

        while (S > maxNeededSize) {
            if (prev(end(s)) == notOnesNext.back())
                notOnesNext.pop_back();
            s.pop_back();
            --S;
        }

        notOnes = move(notOnesNext);
    }

    for (auto elt : s)
        cout << elt << " ";
}

class Solver448ETest : public ProblemTest {};

TEST_F(Solver448ETest, Example1)
{
    string input = R"(6 1
)";
    string output = R"(1 2 3 6 
)";
    setInput(input);
    Solver448E().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver448ETest, Example2)
{
    string input = R"(4 2
)";
    string output = R"(1 1 2 1 2 4 
)";
    setInput(input);
    Solver448E().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver448ETest, Example3)
{
    string input = R"(10 3
)";
    string output = R"(1 1 1 2 1 1 5 1 1 2 1 5 1 2 5 10 
)";
    setInput(input);
    Solver448E().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver448ETest, Example4) {
    string input = R"(963761198400 6553
)";
    setInput(input);
    Solver448E().run();
}

