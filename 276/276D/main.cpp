#include <iostream>
#include <vector>
#include <deque>
#include <cassert>
#include <string>
#include <algorithm>
#include <set>
#include <cstdint>

using namespace std;

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

int main()
{
#ifndef ONLINE_JUDGE  
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif
    int nChilds;
    cin >> nChilds;

    deque<int> ch(nChilds);
    for (int& charisma : ch)
        cin >> charisma;

    ch.push_front(ch.front());
    ch.push_back(ch.back());

    vector<int64_t> dynRes;
    dynRes.push_back(0);
    dynRes.push_back(0);

    int lastExtremalInd = 1;
    for (int i = 2; i < ch.size() - 1; ++i)
    {
        int64_t curres = max(dynRes[lastExtremalInd] + abs(ch[i] - ch[lastExtremalInd + 1]),
            dynRes[lastExtremalInd - 1] + abs(ch[i] - ch[lastExtremalInd]));
        dynRes.push_back(curres);
        if (sgn(ch[i] - ch[i - 1]) != sgn(ch[i + 1] - ch[i]))
            lastExtremalInd = i;
    }

    cout << dynRes.back();

    return 0;
}