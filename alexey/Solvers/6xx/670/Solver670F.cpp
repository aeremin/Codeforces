#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/FunctorIterator.hpp"
using namespace std;

class Solver670F {
public:
    void run();

    int intLog10(int v) {
        int res = 0;
        int pow = 1;
        while (pow <= v) {
            pow *= 10;
            ++res;
        }
        return res;
    }
};

void Solver670F::run() {
    string s, t;
    cin >> s >> t;

    if (s == "00") {
        cout << 0;
        return;
    }

    vector<int> digitCounts(10);
    for (auto d : s)
        ++digitCounts[d - '0'];

    for (auto d : t)
        --digitCounts[d - '0'];

    auto calcLen = [&](int numberLen) {return numberLen + intLog10(numberLen); };
    auto numberLen = lower_bound(makeFunctorIterator(1, calcLen), makeFunctorIterator(int(1e6), calcLen), s.length()).getParameter();
    
    if (t.length() == numberLen) {
        cout << t;
        return;
    }

    while (numberLen) {
        int d = numberLen % 10;
        --digitCounts[d];
        numberLen /= 10;
    }

    string minimalPossibleNumber;
    for (int i : range(10))
        minimalPossibleNumber.append(string(digitCounts[i], '0' + i));

    auto minNonZeroDigit = 1;
    while (minNonZeroDigit < 10 && digitCounts[minNonZeroDigit] == 0)
        ++minNonZeroDigit;

    if (minNonZeroDigit == 10) {
        cout << (t + string(digitCounts[0], '0'));
        return;
    }
    
    digitCounts[minNonZeroDigit]--;

    string  firstDigitBlock;
    firstDigitBlock.push_back('0' + minNonZeroDigit);
    vector<string> blocks = { firstDigitBlock };
    for (int i : range(10))
        if (digitCounts[i] > 0)
            blocks.push_back(string(digitCounts[i], '0' + i));

    vector<string> possibleNumbers;
    if (t[0] != '0')
        possibleNumbers.push_back(t + minimalPossibleNumber);

    for (auto i : range<int>(1, blocks.size() + 1)) {
        string cand;
        for (auto j : range(i))
            cand.append(blocks[j]);
        cand.append(t);
        for (auto j : range<int>(i, blocks.size()))
            cand.append(blocks[j]);

        if (cand[0] != '0')
            possibleNumbers.push_back(cand);
    }

    cout << *min_element(begin(possibleNumbers), end(possibleNumbers));
}


class Solver670FTest : public ProblemTest {};


TEST_F(Solver670FTest, Example1) {
    string input = R"(003512
021
)";
    string output = R"(30021
)";
    setInput(input);
    Solver670F().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver670FTest, Example2) {
    string input = R"(199966633300
63
)";
    string output = R"(3036366999
)";
    setInput(input);
    Solver670F().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

