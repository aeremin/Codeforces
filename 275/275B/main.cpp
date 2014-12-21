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

struct Query
{
    int l, r;
    uint64_t q;
};

int blockSize;

int main()
{
#ifndef ONLINE_JUDGE  
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    int nElts, nQueries;

    cin >> nElts >> nQueries;

    vector<uint64_t> elts(nElts, 0);
    vector<Query> queries(nQueries);
    for (auto& query : queries)
        cin >> query.l >> query.r >> query.q;
    
    blockSize = sqrt(nElts);

    vector<uint64_t> eltBlock(nElts / blockSize + 1, 0);
    
    for (auto query : queries)
    {
        query.l--;
        query.r--;
        int ind = query.l;
        while (ind <= query.r && ind % blockSize != 0)
        {
            elts[ind] |= query.q;
            ++ind;
        }

        while (ind + blockSize - 1 <= query.r)
        {
            eltBlock[ind / blockSize] |= query.q;
            ind += blockSize;
        }

        while (ind <= query.r)
        {
            elts[ind] |= query.q;
            ++ind;
        }
    }

    for (int i = 0; i < nElts; ++i)
        elts[i] |= eltBlock[i / blockSize];

    vector<uint64_t> andBlocks(nElts / blockSize + 1, numeric_limits<uint64_t>::max());
    for (int i = 0; i < nElts; ++i)
        andBlocks[i / blockSize] &= elts[i];

    bool good = true;
    
    for (auto query : queries)
    {
        query.l--;
        query.r--;
        int ind = query.l;
        uint64_t queryRes = numeric_limits<uint64_t>::max();
        while (ind <= query.r && ind % blockSize != 0)
        {
            queryRes &= elts[ind];
            ++ind;
        }

        while (ind + blockSize - 1 <= query.r)
        {
            queryRes &= andBlocks[ind / blockSize];
            ind += blockSize;
        }

        while (ind <= query.r)
        {
            queryRes &= elts[ind];
            ++ind;
        }

        good = good && (queryRes == query.q);
    }

    if (good)
    {
        cout << "YES\n";
        for (auto elt : elts)
            cout << elt << ' ';
    }
    else
    {
        cout << "NO\n";
    }

    return 0;
}