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

int n, m, k;
vi loops, endss;

bool possible(int l){
    vi leftovers;
    int ans = 0;
    for (int i = 0; i < endss.size(); i++){
        ans += endss[i] / (2*l + 1);
        leftovers.push_back(endss[i] % (2 * l + 1));
    }
    for (int i = 0; i < loops.size(); i++){
        ans += loops[i] / (2 * l + 1);
        leftovers.push_back(((loops[i] % (2 * l + 1))+1)/2);
    }
    if (ans > k) return false;
    sort(leftovers.begin(), leftovers.end());
    int ss = leftovers.size();
    int ptr = ss - 1;
    while ((ptr>=0) && (leftovers[ptr] > l)) {
        ptr--; ans++;
    }
    if (ptr==(ss-1)) ans++;
    else if ((ptr >= 0) && ((leftovers[ptr+1] - l - 1 + leftovers[ptr]) >= l)) ans++;
    if (ans > k) return false;
    else return true;
}

int main()
{
    //freopen("h.in", "rt", stdin);
    //freopen("h.out", "wt", stdout);
    cin >> n >> m >> k;
    if (n == k){
        cout << 0;
        return 0;
    }
    vvi nb(n+1);
    for (int i = 0; i < m; i++){
        int x, y;
        cin >> x >> y;
        nb[x].push_back(y);
        nb[y].push_back(x);
    }
    int super = 0;
    for (int i = 1; i <= n; i++){
        if (nb[i].size() > 2) {
            super = i;
            break;
        }
    }
    if (super == 0){
        int l = (((n + k - 1) / k)) / 2;
        cout << l;
        return 0;
    }

    vb used(n + 1, false);
    used[super] = true;
    for (int j = 0; j < nb[super].size(); j++) {
        int v = nb[super][j];
        if (used[v]) continue;
        int len = 1;
        int prev = super;
        while (nb[v].size() == 2){
            len++;
            int swap = v;
            v = nb[v][0] + nb[v][1] - prev;
            prev = swap;            
        }
        if (v == super) {
            used[prev] = true;
            loops.push_back(len-1);
        }
        else{
            endss.push_back(len);
        }
    }
    int minl = 1;
    int maxl = n;
    while (maxl - minl > 1){
        int midl = (maxl + minl) / 2;
        if (possible(midl)) maxl = midl;
        else minl = midl+1;
    }
    if (possible(minl)) cout << minl;
    else cout << maxl;


    return 0;
}