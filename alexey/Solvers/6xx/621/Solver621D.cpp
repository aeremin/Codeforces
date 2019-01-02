#include <Solvers/pch.h>

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/621/problem/D
class Solver621D
{
public:
    void run();
};

void Solver621D::run()
{
    vector<string> formulas =
    {
        "x^y^z", "x^z^y", "(x^y)^z", "y^x^z", "y^z^x", "(y^x)^z", "z^x^y", "z^y^x", "(z^x)^y"
    };
    vector<function<complex<double>(complex<double>, complex<double>, complex<double>)>> functors = 
    {
        [](complex<double> x, complex<double> y, complex<double> z) {return log(log(x)) + z * log(y); },
        [](complex<double> x, complex<double> y, complex<double> z) {return log(log(x)) + y * log(z); },
        [](complex<double> x, complex<double> y, complex<double> z) {return log(log(x)) + log(y) + log(z); },
        
        [](complex<double> x, complex<double> y, complex<double> z) {return log(log(y)) + z * log(x); },
        [](complex<double> x, complex<double> y, complex<double> z) {return log(log(y)) + x * log(z); },
        [](complex<double> x, complex<double> y, complex<double> z) {return log(log(y)) + log(x) + log(z); },
        
        [](complex<double> x, complex<double> y, complex<double> z) {return log(log(z)) + y * log(x); },
        [](complex<double> x, complex<double> y, complex<double> z) {return log(log(z)) + x * log(y); },
        [](complex<double> x, complex<double> y, complex<double> z) {return log(log(z)) + log(x) + log(y); },
    };

    double xr, yr, zr;
    cin >> xr >> yr >> zr;
    complex<double> x = { xr, 0.0 }, y = { yr, 0.0 }, z = { zr, 0.0 };
    vector<complex<double>> results;
    for (auto f : functors)
        results.push_back(f(x, y, z));

    auto compareExponentsOf = [](complex<double> a, complex<double> b) -> bool
    {
        double aSign = abs(a.imag()) > 0.001 ? -1.0 : 1.0;
        double bSign = abs(b.imag()) > 0.001 ? -1.0 : 1.0;
        if ( aSign == bSign )
            return ( a.real() * aSign < b.real() * bSign );
        else
            return aSign < bSign;
    };

    auto maxIndex = max_element(begin(results), end(results), compareExponentsOf) - begin(results);
    cout << formulas[maxIndex];
}

class Solver621DTest : public ProblemTest {};

TEST_F(Solver621DTest, Example1)
{
    string input = R"(1.1 3.4 2.5
)";
    string output = R"(z^y^x
)";
    setInput(input);
    Solver621D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver621DTest, Example2)
{
    string input = R"(2.0 2.0 2.0
)";
    string output = R"(x^y^z
)";
    setInput(input);
    Solver621D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


TEST_F(Solver621DTest, Example3)
{
    string input = R"(1.9 1.8 1.7
)";
    string output = R"((x^y)^z
)";
    setInput(input);
    Solver621D().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


