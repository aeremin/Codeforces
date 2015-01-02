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
    int n, t;
    cin >> n >> t;

    vector<bool> can(n);
    can[0] = true;

    for (int i = 0; i < n - 1; ++i)
    {
        int dist;
        cin >> dist;
        if (can[i]) can[i + dist] = true;
    }

    cout << (can[t - 1] ? "YES" : "NO");
    return 0;
}