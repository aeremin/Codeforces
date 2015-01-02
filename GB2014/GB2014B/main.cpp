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

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i)
    {
        int t; cin >> t;
        p.push_back(t);
    }

    for (int i = 0; i < n; ++i) parent.push_back(i);

    vector<vector<char>> can;
    for (int i = 0; i < n; ++i)
    {
        can.push_back(vector<char>());
        for (int j = 0; j < n; ++j)
        {
            char canc;//= getchar();
            cin >> canc;
            can[i].push_back(canc);
        }
        //getchar();
    }

    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
        {
            // j > i
            if (can[i][j] == '1')
                union_sets(i, j);
        }

    vector<int> res(n);
    vector<bool> taken(n, false);

    for (int i = 0; i < n; ++i)
    {
        if (taken[i]) continue;

        vector<pair<int, int>> group;
        for (int j = i; j < n; ++j)
        {
            if (find_set(j) == find_set(i))
            {
                group.push_back(make_pair(p[j], j));
                taken[j] = true;
            }
        }

        sort(begin(group), end(group), [](pair<int, int> a, pair<int, int> b)
        {
            return a.first < b.first;
        });

        auto groupcopy = group;
        sort(begin(groupcopy), end(groupcopy), [](pair<int, int> a, pair<int, int> b)
        {
            return a.second < b.second;
        });

        for (int k = 0; k < group.size(); ++k)
        {
            res[groupcopy[k].second] = group[k].first;
        }
    }

    for (int i = 0; i < n; ++i)
        cout << res[i] << ' ';
}