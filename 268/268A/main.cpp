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

    int n;
    cin >> n;

    if (n < 4)
    {
        cout << "NO";
        return 0;
    }

    cout << "YES" << endl;
    int s;
    if (n % 2 == 0)
    {
        cout << "1 * 2 = 2" << endl;
        cout << "2 * 3 = 6" << endl;
        cout << "6 * 4 = 24" << endl;
        s = 5;
    }
    else
    {
        cout << "1 + 5 = 6" << endl;
        cout << "4 * 6 = 24" << endl;
        cout << "3 - 2 = 1" << endl;
        cout << "24 * 1 = 24" << endl;
        s = 6;
    }

    for (int i = s; i < n; i+= 2)
    {
        cout << i + 1 << " - " << i << " = 1" << endl;
        cout << "24 * 1 = 24" << endl;
    }

    return 0;
}