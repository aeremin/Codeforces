#include <Solvers/pch.h>

using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/245/problem/H
class Solver245H
{
public:
    void run();
};

void Solver245H::run()
{
    string s; 
    cin >> s;
    auto n = s.length();
    vector<vector<char>> isPalindrome(n, vector<char>(n));
    vector<vector<int>> ans(n, vector<int>(n));
    for (int len = 1; len <= n; ++len)
    {
        for (int i = 0; i <= n - len; ++i)
        {
            if (len == 1)
            {
                isPalindrome[i][i + len - 1] = true;
                ans[i][i + len - 1] = 1;
            }
            else
            {
                isPalindrome[i][i + len - 1] = (s[i] == s[i + len - 1] &&
                                                (len == 2 || isPalindrome[i + 1][i + len - 2]));
                ans[i][i + len - 1] = isPalindrome[i][i + len - 1] ? 1 : 0;
                ans[i][i + len - 1] += ans[i + 1][i + len - 1];
                ans[i][i + len - 1] += ans[i][i + len - 2];
                if (len > 2)
                    ans[i][i + len - 1] -= ans[i + 1][i + len - 2];
            }
        }
    }

    int nQueries; 
    cin >> nQueries;
    for (int i = 0; i < nQueries; ++i)
    {
        int l, r;
        cin >> l >> r;
        cout << ans[l - 1][r - 1] << "\n";
    }
}

class Solver245HTest : public ProblemTest
{
};

TEST_F( Solver245HTest, Example1 )
{
    setInput(
     R"(caaaba
        5
        1 1
        1 4
        2 3
        4 6
        4 5)");
    Solver245H().run();
    EXPECT_EQ("1\n7\n3\n4\n2\n", getOutput());
}