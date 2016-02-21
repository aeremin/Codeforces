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

int gcd(int a, int b){
    if (b == 0) return a;
    if (a == 0) return b;
    if (a > b) return gcd(b, a%b);
    return gcd(a, b%a);
}

int main()
{
    //freopen("problem.in", "rt", stdin);
    //freopen("problem.out", "wt", stdout);

    int t;
    cin >> t;
    for (int ak = 0; ak < t; ak++) {
        int n;
        cin >> n;
        vi c(n);
        vi num(n);
        long long b = 0, w = 0;
        for (int i = 0; i < n; i++) {
            int v;
            cin >> v;
            num[i] = v;
            char cb;
            cin >> cb;
            switch(cb){
            case 'B': 
                c[i] = 0;
                b += v;
                break;
            case 'W': 
                c[i] = 1;
                w += v;
            }
        }
        if (b == 0){
            cout << w << endl;
            continue;
        }
        if (w == 0){
            cout << b << endl;
            continue;
        }
        int ans = 0;
        ll bb = b / gcd(w, b);
        ll ww = w / gcd(w, b);
        ll curb = 0;
        ll curw = 0;
        for (int i = 0; i < n; i++){
            if (c[i] == 0) {
                if ((curb*ww >= bb*curw) || ((curw % ww) != 0)) {
                    curb += num[i];
                    continue;
                }
                else if ((curb + num[i])*ww >= bb*curw) {
                    curb = curb + num[i] - (bb*curw) / ww;
                    curw = 0;
                    ans++;
                    continue;
                }
                else {
                    curb += num[i];
                    continue;
                }
            }
            else if(c[i] == 1) {
                if ((curw*bb >= ww*curb) || ((curb % bb) != 0)) {
                    curw += num[i];
                    continue;
                }
                else if ((curw + num[i])*bb >= ww*curb) {
                    curw = curw + num[i] - (ww*curb) / bb;
                    curb = 0;
                    ans++;
                    continue;
                }
                else {
                    curw += num[i];
                    continue;
                }
            }
        }
        cout << ans << endl;
    }
    return 0;
}