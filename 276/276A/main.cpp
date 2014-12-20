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
    for (int i = 0; i < nQueries; ++i)
    {
        int64_t l, r;
        cin >> l >> r;
        
        if (l == r)
        {
            cout << l << '\n';
            continue;
        }
        
        int64_t maxDifPower = 0;
        int64_t maxDif = 1;
        for (int difPower = 0; difPower < 62; ++difPower)
        {
            if ((r & maxDif) != (l & maxDif))
                maxDifPower = difPower;
            maxDif *= 2;
        }

        int64_t ones = 0;
        maxDif = 1;
        for (int i = 0; i < maxDifPower; ++i)
        {
            ones += maxDif;
            maxDif *= 2;
        }

        int64_t rZeroed = (r >> maxDifPower) << maxDifPower;
        
        int64_t res = rZeroed - 1;
        if ((res + maxDif) <= r)
            res = res + maxDif;

        cout << res << '\n';
    }


    return 0;
}