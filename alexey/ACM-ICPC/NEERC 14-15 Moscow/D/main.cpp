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

int main()
{
    //freopen("problem.in", "rt", stdin);
    //freopen("problem.out", "wt", stdout);
    int a, b;
    cin >> a >> b;

    for (int i = 1; i < 150; i++) {
        if ((i*i == a*a + b*b) || (i*i == b*b - a*a)){
            cout << "YES";
            return 0;
        }
    }
    cout << "NO";

    return 0;
}