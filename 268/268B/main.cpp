
#include <iostream>
#include <vector>
#include <deque>
#include <cassert>
#include <string>
#include <algorithm>
#include <set>
#include <cstdint>
#include <limits>
#include <unordered_map>

using namespace std;

int main()
{
#ifndef ONLINE_JUDGE  
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    unordered_map<int, int> nums;
    vector<int> result;
    vector<bool> used;
    vector<pair<int, int>> edges;

    int n, a, b;
    cin >> n >> a >> b;
    for (int i = 0; i < n; ++i)
    {
        int p;
        cin >> p;
        nums.emplace(p, i);
        used.push_back(false);
        result.push_back(0);
    }

    edges.resize(n);

    for (auto x : nums)
    {
        int ax = a - x.first;
        int bx = b - x.first;
        if (nums.find(ax) != end(nums))
            edges[x.second].first = nums[ax];
        else
            edges[x.second].first = -1;

        if (nums.find(bx) != end(nums))
            edges[x.second].second = nums[bx];
        else
            edges[x.second].second = -1;
    }

    bool res = true;
    for (auto x : nums)
    {
        if (used[x.second]) continue;
        if (min(edges[x.second].first, edges[x.second].second) >= 0) continue;

        used[x.second] = true;
        int cur = x.second;
        int len = 0;
        bool isFirst = edges[x.second].first >= 0;
        int to = isFirst ? 0 : 1;
        do 
        {
            ++len;
            result[cur] = to;
            used[cur] = true;
            cur = (isFirst ? edges[cur].first : edges[cur].second);
            isFirst = !isFirst;
        } while (cur != -1);
        if (len % 2 == 1)
        {
            res = false;
            break;
        }
    }
    
    if (!res)
    {
        cout << "NO";
        return 0;
    }

    cout << "YES" << endl;
    for (int elt : result)
        cout << elt << ' ';

    return 0;
}