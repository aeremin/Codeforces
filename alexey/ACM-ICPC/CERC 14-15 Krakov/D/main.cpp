#include <iostream>
#include <vector>
#include <deque>
#include <cassert>
#include <string>
#include <algorithm>
#include <set>
#include <cstdint>
#include <limits>
#include <cmath>

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
    for (int ak = 0; ak < t; ak++){
        int n;
        cin >> n;
        vi x(n);
        vi y(n);
        vi r(n);
        for (int i = 0; i < n; i++) cin >> x[i] >> y[i] >> r[i];
        vvi e(n);
        for (int i = 0; i < n; i++){
            for (int j = i + 1; j < n; j++){
                if (((x[i] - x[j])*(x[i] - x[j]) + (y[i] - y[j])*(y[i] - y[j])) == (r[i] + r[j])*(r[i] + r[j])){
                    e[i].push_back(j);
                    e[j].push_back(i);
                }
            }
        }
        vb c(n, false);
        vi dir(n, 0);
        std::deque<int> poisk;
        poisk.push_back(0);
        dir[0] = 1;
        c[0] = true;
        while (poisk.size()>0){
            int v = poisk.front();
            poisk.pop_front();
            for (int j = 0; j < e[v].size(); j++){
                if (!c[e[v][j]]){
                    poisk.push_back(e[v][j]);
                    c[e[v][j]] = true;
                    dir[e[v][j]] = -dir[v];
                }
            }
        }

        for (int i = 0; i < n; i++){
            if (dir[i] == 0){
                cout << "not moving" << endl;
            }
            else{
                int p = r[0] / gcd(r[0], r[i]);
                int q = r[i] / gcd(r[0], r[i]);
                cout << p;
                if (q>1) cout << "/" << q;
                cout << " ";
                if (dir[i] == -1) cout << "counter";
                cout << "clockwise" << endl;
            }
        }

    }
    return 0;
}