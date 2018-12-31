#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
using namespace std;

class Solver630O
{
public:
    void run();
};

void Solver630O::run()
{
    double px, py, vx, vy, a, b, c, d;
    cin >> px >> py >> vx >> vy >> a >> b >> c >> d;
    vector<complex<double>> pts;
    pts.emplace_back(px + b, py);
    pts.emplace_back(px, py + a / 2);
    pts.emplace_back(px, py + c / 2);
    pts.emplace_back(px - d, py + c / 2);
    pts.emplace_back(px - d, py - c / 2);
    pts.emplace_back(px, py - c / 2);
    pts.emplace_back(px, py - a / 2);
    complex<double> center = { px, py };
    
    complex<double> rot = { vx, vy };
    rot /= sqrt(vx * vx + vy * vy);
    for (auto& p : pts)
        p = center + (p - center) * rot;
    
    cout << setprecision(12) << fixed;
    for (auto p : pts)
        cout << p.real() << " " << p.imag() << "\n";
}

class Solver630OTest : public ProblemTest {};

TEST_F(Solver630OTest, Example1)
{
    string input = R"(8 8 0 2 8 3 4 5
)";
    string output = R"(8.000000000000 11.000000000000
4.000000000000 8.000000000000
6.000000000000 8.000000000000
6.000000000000 3.000000000000
10.000000000000 3.000000000000
10.000000000000 8.000000000000
12.000000000000 8.000000000000
)";
    setInput(input);
    Solver630O().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}


