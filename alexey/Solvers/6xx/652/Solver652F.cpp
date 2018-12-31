#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/io/readvector.hpp"
#include "algo/SortWithMapping.hpp"
#include "algo/io/printvector.h"
using namespace std;

class Solver652F
{
public:
    void run();

    int64_t mod(int64_t a, int64_t b) {
        auto res = a % b;
        if (res < 0) res += b;
        return res;
    }
};

void Solver652F::run()
{
    int64_t nAnts, circleLen, time;
    cin >> nAnts >> circleLen >> time;
    vector<int> startPositions, finishPositions;
    int64_t totalMove = 0;
    int64_t modulo = circleLen * nAnts;
    for (int i : range(nAnts)) {
        int p;
        char c;
        cin >> p >> c;
        startPositions.push_back(p);
        int speed = c == 'R' ? 1 : -1;
        finishPositions.push_back(mod(p + time * speed - 1, circleLen) + 1);
        totalMove = (totalMove + speed * time) % modulo;
    }

    sort(begin(finishPositions), end(finishPositions));
    vector<size_t> forwardMap, backwardMap;
    sortWithMappings(startPositions, &forwardMap, &backwardMap);

    int64_t totalMoveCandidate = 0;
    for (int i : range(nAnts))
        totalMoveCandidate = mod(totalMoveCandidate + finishPositions[i] - startPositions[i], modulo);

    assert((totalMove - totalMoveCandidate) % circleLen == 0);
    auto offs = ((totalMove - totalMoveCandidate) / circleLen) % nAnts;
    if (offs < 0) offs += nAnts;

    vector<int> result;
    for (int i : range(nAnts))
        result.push_back(finishPositions[(forwardMap[i] + offs) % nAnts]);

    printVector(result);
}

class Solver652FTest : public ProblemTest {};

TEST_F(Solver652FTest, Example1)
{
    string input = R"(2 4 8
1 R
3 L
)";
    string output = R"(1 3
)";
    output.pop_back();
    setInput(input);
    Solver652F().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver652FTest, Example2)
{
    string input = R"(4 8 6
6 R
5 L
1 R
8 L
)";
    string output = R"(7 4 2 7
)";
    output.pop_back();
    setInput(input);
    Solver652F().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver652FTest, Example3)
{
    string input = R"(4 8 2
1 R
5 L
6 L
8 R
)";
    string output = R"(3 3 4 2
)";
    output.pop_back();
    setInput(input);
    Solver652F().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}
