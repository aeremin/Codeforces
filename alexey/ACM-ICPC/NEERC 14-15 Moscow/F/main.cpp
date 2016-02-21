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

double dist(double x, double y, double x2, double y2){
    return sqrt((x - x2)*(x - x2) + (y - y2)*(y - y2));
}

int main()
{
    //freopen("f.in", "rt", stdin);
    //freopen("f.out", "wt", stdout);
    int xa, ya, xb, yb, xc, yc, d, v, t, f, w;
    double alex = 0, petr = 0, dima = 0;
    cin >> xa >> ya >> xb >> yb >> xc >> yc;
    cin >> d >> v;
    char c, k;
    cin >> c >> k;
    t = ((c - '0') * 10 + k - '0')*60 - 540;
    cin >> c;
    cin >> c >> k;
    t += (c - '0') * 10 + k - '0';

    cin >> c >> k;
    f = ((c - '0') * 10 + k - '0') * 60;
    cin >> c;
    cin >> c >> k;
    f += (c - '0') * 10 + k - '0';
    cin >> w;
    alex += (dist(xa, ya, xc, yc) + dist(xc, yc, xb, yb)) / v * 60.0;
    alex += d;

    dima = t + f;

    petr = (dist(xa, ya, xb, yb)) / w * 60.0;
    if ((xb - xa)*(yc - ya) == (xc - xa)*(yb - ya)){
        if ((xc - xa)*(xc - xb) <= 0) petr += d;
    }
    if ((alex < dima) && (alex < petr)){
        cout << "Alex";
    }
    else if ((dima < alex) && (dima < petr)){
        cout << "Dmitry";
    }
    else cout << "Petr";
    return 0;
}