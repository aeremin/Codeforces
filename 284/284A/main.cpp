
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

int64_t sgn(int64_t x)
{
    return x > 0 ? 1 : -1;
}

int main()
{
#ifndef ONLINE_JUDGE  
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    int64_t xH, yH;
    cin >> xH >> yH;
    int64_t xU, yU; 
    cin >> xU >> yU;

    int64_t nRoads;
    cin >> nRoads;

    int64_t steps = 0;
    for (int64_t i = 0; i < nRoads; ++i)
    {
        int64_t a, b, c;
        cin >> a >> b >> c;
        if (sgn(xH * a + yH * b + c) != sgn(xU * a + yU * b + c))
            steps++;
    }

    cout << steps;
    
    return 0;
}