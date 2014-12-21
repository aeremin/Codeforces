
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

    deque<int> ans;

    int dif = 0;
    for (int i = 0; i <= k; ++i)
    {
        ans.push_back(dif);
        if (i % 2 == 0)
            dif = -dif + 1;
        else
            dif = -dif;
    }

    int last = ans.back();
    if (last <= 0)
    {
        while (ans.size() < n)
        {
            last--;
            ans.push_back(last);
        }

        for (int elt : ans)
            cout << elt - last + 1 << ' ';
    }
    else
    {
        while (ans.size() < n)
        {
           last++;
           ans.push_back(last);
        }

        for (int elt : ans)
            cout << elt + n - last << ' ';
    }

    return 0;
}