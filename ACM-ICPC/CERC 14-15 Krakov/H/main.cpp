#include <iostream>
#include <vector>
#include <deque>
#include <cassert>
#include <string>
#include <algorithm>
#include <set>
#include <cstdint>
#include <limits>

using namespace std;

typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef vector<bool> vb;
typedef int64_t ll;

bool precedes(int a, int b)
{
    if (a == b)
        return true;

    if (b == 0)
        return (a % 3 != 0);

    if (a == 0)
        return false;
    
    return ((b - 1) % 3 >= (a - 1) % 3) && ((b - 1) / 3 >= (a - 1) / 3);
}

int main()
{
    //freopen("h.in", "rt", stdin);
    //freopen("h.out", "wt", stdout);

    int nTest;
    cin >> nTest;

    for (int iTest = 0; iTest < nTest; ++iTest)
    {
        int tt;
        cin >> tt;
        int minDIst = 300;
        int best = -1;
        for (int a = 0; a < 10; a++)
        {
            if (abs(a - tt) < minDIst)
            {
                minDIst = abs(a - tt);
                best = a;
            }
        }

        for (int a = 1; a < 10; a++)
            for (int b = 0; b < 10; b++)
        {
            if (precedes(a, b) && abs(a * 10 + b - tt) < minDIst)
            {
                minDIst = abs(a * 10 + b - tt);
                best = a * 10 + b;
            }
        }

        for (int a = 1; a < 3; a++)
            for (int b = 0; b < 10; b++)
                for (int c = 0; c < 10; c++)
        {
            if (precedes(a, b) && precedes(b, c) && abs(a * 100 + b * 10 + c - tt) < minDIst)
            {
                minDIst = abs(a * 100 + b * 10 + c - tt);
                best = a * 100 + b * 10 + c;
            }
        }

        cout << best << endl;
    }

    return 0;
}