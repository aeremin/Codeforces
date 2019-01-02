#include <Solvers/pch.h>
#include "math/pi.h"
#include "algo/binaryfunctors/FirstArgument.hpp"
#include "algo/updatetypes/LinearTransform.hpp"
#include "algo/updateappliers/LinearTransformIdempotent.h"
#include "algo/SegmentTree.hpp"

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/618/problem/E
class Solver618E
{
public:
    void run();
};

void Solver618E::run()
{
    int n, m;
    cin >> n >> m;
    vector<complex<double>> points(n + 1);
    for (int i = 0; i <= n; ++i)
        points[i] = { i + 0.0, 0.0 };

    
    typedef updateTypes::LinearTransform<complex<double>> TransformType;

    cout << setprecision(10) << fixed;
    auto segmentTree = makeSegmentTree(points, binaryFunctors::FirstArgument<complex<double>>(), TransformType());
    for (int i = 0; i < m; ++i)
    {
        int x, y, z;
        cin >> x >> y >> z;
        auto red = segmentTree.getValueOnSegment(y - 1, y);
        auto blue = segmentTree.getValueOnSegment(y, y + 1);
        if (x == 1)
        {
            auto shift = double(z) * (blue - red) / abs(blue - red);
            segmentTree.updateRange(y, n + 1, TransformType({ 1.0, 0.0 }, shift));
        }
        else
        {
            auto rot = polar(1.0, -double(z) / 180.0 * kPi);
            segmentTree.updateRange(y, n + 1, TransformType(rot, red * (complex<double>(1, 0) - rot)));
        }
        auto last = segmentTree.getValueOnSegment(n, n + 1);
        cout << last.real() << " " << last.imag() << " ";
    }
}

class Solver618ETest : public ProblemTest {};

TEST_F(Solver618ETest, Example1)
{
    setInput("5 4             1 1 3             2 3 90             2 5 48             1 4 1");
    Solver618E().run();
    EXPECT_EQ("8.0000000000 0.0000000000 5.0000000000 -3.0000000000 4.2568551745 -2.6691306064 4.2568551745 -3.6691306064 ", getOutput());
}

TEST_F(Solver618ETest, Example2)
{
    // Time-estimation test
    int n = 300000;
    string input = to_string(n) + " " + to_string(n) + " ";
    for (int i = 0; i < n; ++i)
        input.append("1 1 1 ");
    setInput(input);
    Solver618E().run();
}




