#include <Solvers/pch.h>

using namespace std;

class Solver621C
{
public:
    void run();
};

void Solver621C::run()
{
    int n, prime;
    cin >> n >> prime;
    vector<pair<int, int>> intervals(n);
    for (auto& p : intervals)
        cin >> p.first >> p.second;

    vector<double> probs;
    
    auto probByInterval = [&](pair<int, int> p) -> double
    {
        return double(p.second / prime - (p.first - 1) / prime) / double(p.second - p.first + 1);
    };

    transform(begin(intervals), end(intervals), back_inserter(probs), probByInterval);

    double ans = 0.0;
    for (int i = 0; i < n; ++i)
    {
        auto pC = probs[i];
        auto pL = probs[(i + n - 1) % n];
        auto pR = probs[(i + 1) % n];
        ans += 1.0 - (1 - pC) * (1 - pL);
        ans += 1.0 - (1 - pC) * (1 - pR);
    }

    cout << setprecision(10) << fixed << (1000 * ans);
}

class Solver621CTest : public ProblemTest {};

TEST_F(Solver621CTest, Example1)
{
    string input = R"(3 2
1 2
420 421
420420 420421
)";
    string output = R"(4500.0000000000
)";
    setInput(input);
    Solver621C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver621CTest, Example2)
{
    string input = R"(3 5
1 4
2 3
11 14
)";
    string output = R"(0.0000000000
)";
    setInput(input);
    Solver621C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


