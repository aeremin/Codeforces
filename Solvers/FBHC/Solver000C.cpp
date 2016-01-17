#include <Solvers/pch.h>

using namespace std;

class Solver000C
{
public:
    void run();
    void runOneTest();

    vector<int64_t> partPrices, partPricesSums;

    double integrate(int64_t R) const
    {
        double result = 0;
        for (int i = 0; i < partPrices.size(); ++i)
        {
            auto l = partPricesSums[i];
            auto r = partPricesSums[i + 1];
            if (l >= R)
                break;
            r = min(r, R);
            result += (r - l) * l;
        }
        return result;
    }
    
    double answer(int64_t b) const
    {
        if (b == 0)
            return 0;
        int64_t c = partPricesSums.back();
        int64_t d = b / c;
        int64_t rem = b - d * c;
        double res = ( 0.5 * double(d) * double(c) * double(c) + 0.5 * double(rem) * double(rem) - (d * integrate(c) + integrate(rem))) / double(b);
        return res;
    }
};

void Solver000C::run()
{
    int t;
    cin >> t;
    for (int i = 0; i < t; ++i)
    {
        cout << "Case #" << (i + 1) << ": ";
        runOneTest();
        if (i != t - 1) cout << "\n";
    }
}

void Solver000C::runOneTest()
{
    int64_t nPrices, A, B;
    cin >> nPrices >> A >> B;
    partPrices = vector<int64_t>(nPrices);
    for (auto& p : partPrices)
        cin >> p;

    partPricesSums = { 0 };
    partial_sum(begin(partPrices), end(partPrices), back_inserter(partPricesSums));

    double ans = + double(B) / double(B - A) * answer(B) - double(A) / double(B - A) * answer(A);
    cout << setprecision(9) << fixed << ans;
}

class Solver000CTest : public ProblemTest
{
};

TEST_F(Solver000CTest, Example) {
  setInput(
      R"(6
1 5 8
2
1 0 777777777
7
1 777777 7777777
777777777
2 9 20
8 2
5 40 140
4 9 1 12 7
5 1000 2004
4 4 4 4 4
)");

  std::string expected =
R"(Case #1: 1.166666667
Case #2: 3.500000000
Case #3: 4277777.000000000
Case #4: 3.227272727
Case #5: 4.400000000
Case #6: 2.000000000)";
  Solver000C().run();
  EXPECT_EQ(expected, getOutput());
}