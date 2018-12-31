#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/io/readvector.hpp"
#include "algo/SortWithMapping.hpp"
#include "algo/updatetypes/SetTo.hpp"
#include "algo/updateappliers/SetToIdempotent.h"
#include "algo/SegmentTree.hpp"
#include "algo/binaryfunctors/Min.hpp"
#include "algo/FunctorIterator.hpp"
#include "algo/io/printvector.h"

using namespace std;

class Solver377B
{
public:
    void run();
};

void Solver377B::run()
{
    int nStudents, nBugs, maxPrice;
    cin >> nStudents >> nBugs >> maxPrice;
    auto difficulties = readVector<int64_t>(nBugs);
    auto skills = readVector<int64_t>(nStudents);
    auto prices = readVector<int64_t>(nStudents);

    vector<size_t> studBackwM;
    sortWithMappings(skills, nullptr, &studBackwM);

    vector<pair<int64_t, int>> pricesPermuted(prices.size());
    for (int i : range(nStudents))
        pricesPermuted[i] = make_pair( prices[studBackwM[i]], i );

    vector<size_t> bugsBackwM;
    sortWithMappings(difficulties, nullptr, &bugsBackwM);

    auto tryToFitIn = [&](int days) -> int {
        auto st = makeSegmentTree(pricesPermuted, binaryFunctors::Min<pair<int64_t, int>>(), updateTypes::SetTo<pair<int64_t, int>>());
        int64_t totalPrice = 0;
        for (int i = nBugs - 1; i >= 0; i -= days) {
            auto d = difficulties[i];
            auto skillInd = lower_bound(begin(skills), end(skills), d) - begin(skills);
            if (skillInd == nStudents)
                return 0;

            auto minPriceData = st.getValueOnSegment(skillInd, nStudents);
            totalPrice += minPriceData.first;
            st.updateElement(minPriceData.second, updateTypes::SetTo<pair<int64_t, int>>(make_pair(numeric_limits<int>::max(), 0)));
            if (totalPrice > maxPrice)
                return 0;
        }

        return 1;
    };

    auto l = makeFunctorIterator(1, tryToFitIn);
    auto r = makeFunctorIterator(nBugs + 1, tryToFitIn);

    auto it = lower_bound(l, r, 1);
    if (it == r) {
        cout << "NO";
    }
    else {
        vector<int> fixer(nBugs);
        auto days = it.getParameter();
        auto st = makeSegmentTree(pricesPermuted, binaryFunctors::Min<pair<int64_t, int>>(), updateTypes::SetTo<pair<int64_t, int>>());
        for (int i = nBugs - 1; i >= 0; i -= days) {
            auto d = difficulties[i];
            auto skillInd = lower_bound(begin(skills), end(skills), d) - begin(skills);
            auto minPriceData = st.getValueOnSegment(skillInd, nStudents);
            st.updateElement(minPriceData.second, updateTypes::SetTo<pair<int64_t, int>>(make_pair(numeric_limits<int>::max(), 0)));
            for (int j : range(max(0, i - days + 1), i + 1))
                fixer[bugsBackwM[j]] = studBackwM[minPriceData.second] + 1;
        }
        cout << "YES\n";
        printVector(fixer);
    }
}

class Solver377BTest : public ProblemTest {};

TEST_F(Solver377BTest, Example1)
{
    string input = R"(3 4 9
1 3 1 2
2 1 3
4 3 6
)";
    string output = R"(YES
2 3 2 3
)";
    output.pop_back();
    setInput(input);
    Solver377B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver377BTest, Example2)
{
    string input = R"(3 4 10
2 3 1 2
2 1 3
4 3 6
)";
    string output = R"(YES
1 3 1 3
)";
    output.pop_back();
    setInput(input);
    Solver377B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver377BTest, Example3)
{
    string input = R"(3 4 9
2 3 1 2
2 1 3
4 3 6
)";
    string output = R"(YES
3 3 2 3
)";
    output.pop_back();
    setInput(input);
    Solver377B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver377BTest, Example4)
{
    string input = R"(3 4 5
1 3 1 2
2 1 3
5 3 6
)";
    string output = R"(NO
)";
    output.pop_back();
    setInput(input);
    Solver377B().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}



