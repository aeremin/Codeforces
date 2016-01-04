#include <Solvers/pch.h>

using namespace std;

class Solver379D
{
public:
    void run();

    struct StringProperties
    {
        bool startsOnC, endsOnA;
        int countOfAC;
    };

    vector<StringProperties> createStringOptions(int stringLen)
    {
        vector<StringProperties> res;
        for (int i = 0; i <= stringLen / 2; ++i)
        {
            res.push_back({ false, false, i });
            if (2 * i + 1 <= stringLen)
            {
                res.push_back({ false, true, i });
                res.push_back({ true, false, i });
            }
            if (2 * i + 2 <= stringLen)
                res.push_back({ true, true, i });
        }
        return res;
    }

    bool isGood(StringProperties p1, StringProperties p2, int k, int x)
    {
        if (k == 1)
            return (p1.countOfAC == x);
        if (k == 2)
            return (p2.countOfAC == x);

        StringProperties p3;
        p3.startsOnC = p1.startsOnC;
        p3.endsOnA = p2.endsOnA;
        p3.countOfAC = p1.countOfAC + p2.countOfAC + ((p1.endsOnA && p2.startsOnC) ? 1 : 0);
        return p3.countOfAC <= x && isGood(p2, p3, k - 1, x);
    }

    string createStringByProperties(int len, StringProperties p)
    {
        string res;
        if (p.startsOnC)
            res.append("C");
        for (int i = 0; i < p.countOfAC; ++i)
            res.append("AC");
        char lastChar = p.endsOnA ? 'A' : 'B';
        res.append(string(len - res.length(), lastChar));
        return res;
    }
};

void Solver379D::run()
{
    int k, x, n, m;
    cin >> k >> x >> n >> m;

    auto firstStringOptions = createStringOptions(n);
    auto secondStringOptions = createStringOptions(m);
    for (auto& p1 : firstStringOptions)
        for (auto& p2 : secondStringOptions)
            if (isGood(p1, p2, k, x))
            {
                cout << createStringByProperties(n, p1) << "\n" << createStringByProperties(m, p2);
                return;
            }
    cout << "Happy new year!";
}

class Solver379DTest : public ProblemTest
{
};

TEST_F(Solver379DTest, Example1)
{
    setInput("3 2 2 2");
    Solver379D().run();
    EXPECT_EQ("AC\nAC", getOutput());
}

TEST_F(Solver379DTest, Example2)
{
    setInput("3 3 2 2");
    Solver379D().run();
    EXPECT_EQ("Happy new year!", getOutput());
}

TEST_F(Solver379DTest, Example3)
{
    setInput("3 0 2 2");
    Solver379D().run();
    EXPECT_EQ("BB\nBB", getOutput());
}

TEST_F(Solver379DTest, Example4)
{
    setInput("4 3 2 1");
    Solver379D().run();
    EXPECT_EQ("Happy new year!", getOutput());
}
