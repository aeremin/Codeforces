
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

    int n, k;
    cin >> n >> k;

    cout << (6 * n - 1) * k << endl;

    for (int i = 0; i < n; ++i)
        cout << k * (1 + 6 * i) << ' ' << k * (2 + 6 * i) << ' ' << k * (3 + 6 * i) << ' ' << k * (5 + 6 * i) << endl;

    return 0;
}