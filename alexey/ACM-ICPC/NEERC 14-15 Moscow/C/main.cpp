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

typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef vector<bool> vb;
typedef int64_t ll;

ll intceil(ll a, ll b)
{
    return (a + b - 1) / b;
}

ll intfloor(ll a, ll b)
{
    return (a / b);
}

ll vDrive, vCont, vTotal;

bool isEnough(ll nDrive, ll nCont)
{
    if (nCont == 0) return false;

    ll total = 0;
    ll drivePerCont = intfloor(nDrive , nCont);
    ll bigCont = nDrive % nCont;
    ll smallCont = nCont - bigCont;
    total += smallCont * min(vCont, drivePerCont * vDrive);
    total += bigCont *   min(vCont, (drivePerCont + 1) * vDrive);
    return (total >= vTotal);
}

int main()
{


    cin >> vDrive >> vCont >> vTotal;

    if (vCont < vDrive)
    {
        ll res = intceil(vTotal , vCont);
        cout << res << ' ' << res;
        return 0;
    }

    ll nDrive = intceil(vTotal , vDrive);

    ll badCont = 0;
    ll goodCont = ll(2e9);

    while (goodCont - badCont > 1)
    {
        auto cCont = (goodCont + badCont) / 2;
        if (isEnough(nDrive, cCont))
            goodCont = cCont;
        else
            badCont = cCont;
    }

    cout << nDrive << ' ' << goodCont;

    return 0;
}