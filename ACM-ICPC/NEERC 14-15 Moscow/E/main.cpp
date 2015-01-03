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

long long n, d;
vector<ll> primes;
vector<int> powers;
long long curK, curR;

void factorize(ll num)
{
    if (num % 2 == 0)
    {
        primes.push_back(2);
        int pow = 0;
        while (num % 2 == 0)
        {
            num /= 2;
            pow++;
        }
        powers.push_back(pow);
    }

    for (ll div = 3; div * div <= num; div += 2)
    {
        if (num % div == 0)
        {
            primes.push_back(div);
            int pow = 0;
            while (num % div == 0)
            {
                num /= div;
                pow++;
            }
            powers.push_back(pow);
        }
    }

    if (num > 1)
    {
        primes.push_back(num);
        powers.push_back(1);
    }
}

void dyn(int pnum, long long curdiv){
    if (pnum < primes.size()){
        long long newdiv = curdiv;
        for (int j = 0; j < powers[pnum]; j++){
            dyn(pnum + 1, newdiv);
            newdiv *= primes[pnum];
        }
        dyn(pnum + 1, newdiv);
    }
    else {
        if (curdiv <= d) return;
        long long del = n;
        int r = 0;
        while ((del - d) % curdiv == 0){
            r++;
            del = (del - d) / curdiv;
        }
        if (r == curR){
            if (curdiv < curK) curK = curdiv;
        }
        if (r > curR){
            curR = r;
            curK = curdiv;
        }
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
    factorize(n - d);
    curR = -1;
    curK = n + 1;
    dyn(0, 1);
    cout << curK << " " << curR;
    return 0;
}