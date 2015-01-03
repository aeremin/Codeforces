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

    int64_t MODULO = 1000000007;

    int64_t a, b;
    cin >> a >> b;

    int64_t r1 = (b * (b - 1)) / 2;
    r1 = r1 % MODULO;

    int64_t r3 = (a * (a + 1)) / 2;
    r3 = r3 % MODULO;

    int64_t r2 = a + b * r3;
    r2 = r2 % MODULO;

    cout << (r1 * r2) % MODULO;

    return 0;
}