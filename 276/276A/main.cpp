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

int main()
{
#ifndef ONLINE_JUDGE  
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif
    int nQueries;
    cin >> nQueries;

    const uint64_t one = 1;
    for (int i = 0; i < nQueries; ++i)
    {
        uint64_t l, r;
        cin >> l >> r;

        if (l == r)
        {
            cout << l << '\n';
            continue;
        }

        int maxDifPow = 1;
        while (l >> maxDifPow != r >> maxDifPow)
            ++maxDifPow;
        uint64_t ones = (one << maxDifPow - 1) - 1;

        if ((r | ones) <= r)
            cout << (r | ones) << endl;
        else
            cout << (l | ones) << endl;
    }


    return 0;
}