#include <Solvers/pch.h>

using namespace std;

class SolverFBHC1C
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

void SolverFBHC1C::run()
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

void SolverFBHC1C::runOneTest()
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

class SolverFBHC1CTest : public FBHCProblemTest
{
public:
    SolverFBHC1CTest() : FBHCProblemTest("Inputs\\FBHC\\Round1\\C\\") {}
};

TEST_F(SolverFBHC1CTest, Example)
{
    SolverFBHC1C().run();
}