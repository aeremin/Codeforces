#include <Solvers/pch.h>
#include "algo/SortWithMapping.hpp"
#include "algo/FunctorIterator.hpp"
#include "algo/Relax.hpp"
#include "algo/Indicator.hpp"

using namespace std;

class Solver613B
{
public:
    void run();
};

void Solver613B::run()
{
    int64_t n, A, cf, cm, m;
    cin >> n >> A >> cf >> cm >> m;

    vector<int64_t> skills(n);
    for (auto& elt : skills)
        cin >> elt;

    vector<size_t> sortMapping;
    sortWithMappings(skills, &sortMapping, nullptr);

    vector<int64_t> prefixSums = { 0 };
    partial_sum(begin(skills), end(skills), back_inserter(prefixSums));

    int64_t maxForce = -1;
    int64_t bestMaximizedSkillsCount = 0;

    for (int64_t maximizedSkillsCount = 0; maximizedSkillsCount <= n; ++maximizedSkillsCount)
    {
        int64_t price = 0;
        int64_t force = 0;
        price += maximizedSkillsCount * A - (prefixSums[n] - prefixSums[n - maximizedSkillsCount]);
        force += cf * maximizedSkillsCount;

        if (price > m)
            continue;

        auto canRiseUpTo = [&](int64_t minValue) -> int
        {
            size_t nNeedToIncrease = lower_bound(begin(skills), begin(skills) + (n - maximizedSkillsCount), minValue) - begin(skills);
            auto price2 = nNeedToIncrease * minValue - prefixSums[nNeedToIncrease];
            return indicator<int>(price2 + price > m);
        };

        auto l = makeFunctorIterator(skills[0], canRiseUpTo);
        auto r = makeFunctorIterator(A + 1, canRiseUpTo);
        int64_t maxAchievableMinimum = lower_bound(l, r, 1).getParameter() - 1;
        force += cm * maxAchievableMinimum;

        if (force > maxForce)
        {
            maxForce = force;
            bestMaximizedSkillsCount = maximizedSkillsCount;
        }
    }

    int64_t minimum = (cm == 0) ? -1 : (maxForce - cf * bestMaximizedSkillsCount) / cm;
    for (int i = 0; i < n; ++i)
    {
        if (i >= n - bestMaximizedSkillsCount)
            skills[i] = A;
        else
            relaxMax(skills[i], minimum);
    }

    cout << maxForce << "\n";
    for (int i = 0; i < n; ++i)
        cout << skills[sortMapping[i]] << " ";
}

class Solver613BTest : public ProblemTest
{
};

TEST_F( Solver613BTest, Example1 )
{
    setInput("3 5 10 1 5             1 3 1");
    Solver613B().run();
    EXPECT_EQ("12\n2 5 2 ", getOutput());
}


TEST_F( Solver613BTest, Example2 )
{
    setInput("3 5 10 1 339             1 3 1");
    Solver613B().run();
    EXPECT_EQ("35\n5 5 5 ", getOutput());
}

TEST_F(Solver613BTest, Example3)
{
    setInput("3 50 100 1 40             10 30 10");
    Solver613B().run();
    EXPECT_EQ("120\n20 50 20 ", getOutput());
}

TEST_F(Solver613BTest, Example4)
{
    setInput("3 50 100 1 0             11 30 11");
    Solver613B().run();
    EXPECT_EQ("11\n11 30 11 ", getOutput());
}