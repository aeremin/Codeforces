#include <Solvers/pch.h>
#include "math/sign.h"

using namespace std;

class Solver074B
{
public:
    void run();
};

void Solver074B::run()
{
    int nCoaches, posStowaway, posController;
    cin >> nCoaches >> posStowaway >> posController;
    string s;
    cin >> s >> s;
    int dirController = (s == "tail") ? 1 : -1;
    string schedule;
    cin >> schedule;
    for (int i = 0; i < schedule.length(); ++i)
    {
        if (schedule[i] == '0')
        {
            if (sgn(posStowaway - posController) == dirController)
                posStowaway += dirController;
            else
                posStowaway -= dirController;
            posStowaway = min(max(1, posStowaway), nCoaches);
        }
        else
        {
            if (dirController == 1)
                posStowaway = 1;
            else
                posStowaway = nCoaches;
        }
        posController += dirController;
        if (posController == 1 || posController == nCoaches)
            dirController *= -1;

        if (posController == posStowaway)
        {
            cout << "Controller " << (i + 1);
            return;
        }
    }
    cout << "Stowaway";
}

class Solver074BTest : public ProblemTest
{
};

TEST_F(Solver074BTest, Example1)
{
    setInput("5 3 2\nto head\n0001001");
    Solver074B().run();
    EXPECT_EQ("Stowaway", getOutput());
}

TEST_F( Solver074BTest, Example2 )
{
    setInput("3 2 1\nto tail\n0001");
    Solver074B().run();
    EXPECT_EQ("Controller 2", getOutput());
}
