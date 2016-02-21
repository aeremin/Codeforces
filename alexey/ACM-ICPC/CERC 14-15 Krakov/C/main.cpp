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

typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef vector<bool> vb;
typedef int64_t ll;

struct Alien
{
    int l, r, d;
};

vector<Alien> aliens;

int SomeBigShit = 60000;
unordered_map<int, int> cache;

int cacher(pair<int, int> a)
{
    return a.first * SomeBigShit + a.second;
}

int minPower(int l, int r)
{
    auto iter = cache.find(cacher({ l, r }));
    if (iter != cache.end())
        return (*iter).second;

    int maxDist = 0;
    Alien distAl;
    for (auto al : aliens)
    {
        if (al.l > l && al.r < r && al.d > maxDist)
        {
            maxDist = al.d;
            distAl = al;
        }
    }

    if (maxDist == 0)
    {
        return 0;
        cache[cacher({l, r})] = 0;
    }

    int result = 1e9;

    for (auto al : aliens)
    {
        if (al.r >= distAl.l && al.r <= distAl.r)
        {
            result = min(result, maxDist + minPower(l, al.r) + minPower(al.r, r));
        }
    }

    cache[cacher({l, r})] = result;
    return result;
}

int main()
{
    //freopen("problem.in", "rt", stdin);
    //freopen("problem.out", "wt", stdout);

    int nTests;
    cin >> nTests;
    for (int iTest = 0; iTest < nTests; ++iTest)
    {
        int nAliens;
        cin >> nAliens;
        aliens.clear();
        aliens.resize(nAliens);
        cache.clear();

        for (auto& al : aliens)
            cin >> al.l >> al.r >> al.d;

        cout << minPower(-20000, 20000) << endl;
    }

    return 0;
}