#include "Solvers/pch.h"

// Solution for Codeforces problem http://codeforces.com/contest/581/problem/D
class Solver581D
{
public:
    void run();
};

struct Rectange
{
    int x, y;
    char c;

    int area() const { return x * y; }
    int hasSide(int len) const { return (x == len || y == len) ? 1 : 0; }

    void rotateSoSideIsX(int len)
    {
        if (y == len)
            swap(x, y);
    }

    void rotate() { swap(x, y); }

    void print() const
    {
        for (int yy = 0; yy < y; ++yy)
        {
            for (int xx = 0; xx < x; ++xx)
                cout << c;
            cout << '\n';
        }
    }
};


void Solver581D::run()
{
    Rectange r1, r2, r3;
    cin >> r1.x >> r1.y;
    cin >> r2.x >> r2.y;
    cin >> r3.x >> r3.y;
    int totalArea = r1.area() + r2.area() + r3.area();
    int side = int( sqrt(totalArea) );
    if (side * side != totalArea)
    {
        cout << "-1";
        return;
    }

    int goodSides = r1.hasSide(side) + r2.hasSide(side) + r3.hasSide(side);
    if (goodSides == 0 || goodSides == 2)
    {
        cout << "-1";
        return;
    }

    r1.c = 'A'; r2.c = 'B'; r3.c = 'C';

    if (goodSides == 3)
    {
        cout << side << endl;
        r1.rotateSoSideIsX(side);
        r2.rotateSoSideIsX(side);
        r3.rotateSoSideIsX(side);
        r1.print();
        r2.print();
        r3.print();
        return;
    }

    if (r2.hasSide(side))
        swap(r2, r1);
    else if (r3.hasSide(side))
        swap(r3, r1);

    r1.rotateSoSideIsX(side);
    
    int anotherSide = side - r1.y;
    if (r2.hasSide(anotherSide) + r3.hasSide(anotherSide) != 2)
    {
        cout << "-1";
        return;
    }

    r2.rotateSoSideIsX(anotherSide);
    r2.rotate();
    r3.rotateSoSideIsX(anotherSide);
    r3.rotate();

    cout << side << endl;
    r1.print();

    for (int y = 0; y < anotherSide; ++y)
    {
        for (int x = 0; x < side; ++x)
            cout << (x < r2.x ? r2.c : r3.c);
        cout << '\n';
    }
}

class Solver581DTest : public ProblemTest {};

TEST_F(Solver581DTest, Example2)
{
    setInput("5 1 2 5 5 2");
    Solver581D().run();
    auto expected = R"(5
AAAAA
BBBBB
BBBBB
CCCCC
CCCCC
)";
    EXPECT_EQ(expected, getOutput());
}

TEST_F(Solver581DTest, Example3)
{
    setInput("4 4 2 6 4 2");
    Solver581D().run();
    auto expected = R"(6
BBBBBB
BBBBBB
AAAACC
AAAACC
AAAACC
AAAACC
)";
    EXPECT_EQ(expected, getOutput());
}

