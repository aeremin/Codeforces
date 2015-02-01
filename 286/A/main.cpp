#include <iostream>
#include <vector>
#include <deque>
#include <cassert>
#include <string>
#include <algorithm>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <limits>

using namespace std;

const int nIslands = 30001;

int step;

int possibleSteps = 4 * sqrt(nIslands);
vector<vector<int>> resultCache(nIslands, vector<int>(possibleSteps, -1));
unordered_map<int, int> resultCache2;


inline int hasher(const pair<int, int>& a)
{
    return (a.first << 15) + a.second;
}

int& access(int iIsland, int iStep)
{
    return resultCache[iIsland][iStep - step + possibleSteps / 2];
}

int& access2(int iIsland, int iStep)
{
    auto h = hasher({ iIsland, iStep });
    auto it = resultCache2.find(h);
    if (it != end(resultCache2))
        return (*it).second;
    resultCache2[h] = -1;
    return resultCache2[h];
}

vector<int> nDiamonds(nIslands, 0);

int maxStep = 0;
int nFromCache = 0;
int nCalculated = 0;

int result(int start, int prevStep)
{
    maxStep = max(maxStep, prevStep);

    if (start >= nIslands)
        return 0;

    auto& cached = access2(start, prevStep);
    if (cached >= 0)
    {
        ++nFromCache;
        //return (*it).second;
        return cached;
    }
    ++nCalculated;

    int r1 = result(start + prevStep + 1, prevStep + 1);
    int r2 = result(start + prevStep, prevStep);
    int r3 = (prevStep > 1) ? result(start + prevStep - 1, prevStep - 1) : 0;

    cached = max(max(r1, r2), r3) + nDiamonds[start];
    return cached;
}

int main()
{
    ios_base::sync_with_stdio(false);
#ifndef ONLINE_JUDGE  
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    int n;
    cin >> n >> step;
    for (int i = 0; i < n; ++i)
    {
        int t;
        cin >> t;
        nDiamonds[t]++;
    }

    cout << nDiamonds[0] + result(step, step) << endl;
    return 0;
}