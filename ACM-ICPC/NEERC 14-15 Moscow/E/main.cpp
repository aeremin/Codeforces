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

ll currK = 2;
int currR = 0;
ll n, d;

void evaluate(ll base)
{
    if (d >= base || base == 1)
        return;

    int nDig = 0;
    auto copyN = n;
    do
    {
        copyN /= base;
        nDig++;
    } while ((copyN - d) % base == 0 && copyN > 0);
    if (nDig > currR || nDig == currR && base < currK)
    {
        currR = nDig;
        currK = base;
    }
}

int main()
{
    //freopen("e.in", "rt", stdin);
    //freopen("e.out", "wt", stdout);
    cin >> n >> d;
    if (n == 0){
        cout << 2 << " ";
        if (d == 0) cout << 1;
        else cout << 0;
        return 0;
    }
    
    if (n < d)
    {
        cout << 2 << ' ' << 0;
        return 0;
    }

    if (n == d)
    {
        cout << n + 1 << ' ' << 1;
        return 0;
    }

    ll maxDivisor = sqrt(n - d);
    for (ll div = 1; div <= maxDivisor; ++div)
    {
        if ((n - d) % div == 0)
        {
            evaluate(div);
            evaluate((n - d) / div);
        }
    }
    cout << currK << " " << currR;
    
    //cin >> currR;
    return 0;
}