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

vector<int> parent;
vector<int> p;

int find_set(int v) {
    if (v == parent[v])
        return v;
    return find_set(parent[v]);
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b)
        parent[b] = a;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    int nBooks, nDays;

    cin >> nBooks >> nDays;

    vector<int> weight;

    for (int i = 0; i < nBooks; ++i)
    {
        int w;
        cin >> w;
        weight.push_back(w);
    }

    vector<int> toread;
    for (int i = 0; i < nDays; ++i)
    {
        int w;
        cin >> w;
        toread.push_back(w - 1);
    }

    int total = 0;


    for (int iBook = 0; iBook < nBooks; ++iBook)
    {
        vector<bool> alreadyCounted(nBooks, false);
        int localTotal = 0;
        for (int iDay = 0; iDay < nDays; ++iDay)
        {
            if (toread[iDay] == iBook)
            {
                total += localTotal;
                fill(begin(alreadyCounted), end(alreadyCounted), false);
                localTotal = 0;
            }
            else
            {
                if (!alreadyCounted[toread[iDay]])
                {
                    localTotal += weight[toread[iDay]];
                    alreadyCounted[toread[iDay]] = true;
                }
            }
        }
    }

    cout << total;

    return 0;
}