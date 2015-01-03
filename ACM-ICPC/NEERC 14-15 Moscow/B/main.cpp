#include <iostream>
#include <vector>
#include <deque>
#include <cassert>
#include <string>
#include <algorithm>
#include <set>
#include <cstdint>
#include <limits>
#include <numeric>

using namespace std;

typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef vector<bool> vb;
typedef int64_t ll;

struct Platoon
{
    int x1, x2, y1, y2;
};

struct  Bomb
{
    int x, y;
    int phor, pvert;
};

struct  BombVert
{
    int x;
    int p;
};

struct  BombHor
{
    int y;
    int p;
};

int search(std::vector<pair<int,double>> & a, int value){
    int lmin = 0, lmax = a.size() - 1;
    if (a[0].first > value) return -1;
    else lmin = 0;
    lmax = a.size() - 1;
    while ((lmax - lmin) > 1){
        int lmed = (lmax + lmin) / 2;
        if (a[lmed].first <= value) lmin = lmed;
        else lmax = lmed;
    }
    if (a[lmax].first <= value) return lmax;
    else return lmin;
}

int main()
{

    int nBombs, nPlatoons;
    cin >> nPlatoons >> nBombs;

    vector<Platoon> platoons(nPlatoons);
    for (auto& p : platoons)
        cin >> p.x1 >> p.y1 >> p.x2 >> p.y2;

    vector<BombHor> bombHor;
    vector<BombVert> bombVert;

    for (int i = 0; i < nBombs; ++i)
    {
        int x, y, p1, p2;
        cin >> x >> y >> p1 >> p2;
        bombHor.push_back({ y, p1 });
        bombVert.push_back({ x, p2 });
    }

    sort(begin(bombHor), end(bombHor), [](BombHor a, BombHor b)
    {
        return a.y < b.y;
    });

    sort(begin(bombVert), end(bombVert), [](BombVert a, BombVert b)
    {
        return a.x < b.x;
    });

    vector < pair<int, double>> bombCondVert, bombCondHor;
    for (int i = 0; i < bombHor.size(); ++i)
    {
        if (i > 0 && (bombHor[i - 1].y == bombHor[i].y))
        {
            double pp = double(bombHor[i].p) / 100.0;
            bombCondHor.back().second = bombCondHor.back().second + pp - bombCondHor.back().second * pp;
        }
        else
        {
            bombCondHor.push_back(make_pair(bombHor[i].y, double(bombHor[i].p) / 100.0));
        }
    }

    for (int i = 0; i < bombVert.size(); ++i)
    {
        if (i > 0 && (bombVert[i - 1].x == bombVert[i].x))
        {
            double pp = double(bombVert[i].p) / 100.0;
            bombCondVert.back().second = bombCondVert.back().second + pp - bombCondVert.back().second * pp;
        }
        else
        {
            bombCondVert.push_back(make_pair(bombVert[i].x, double(bombVert[i].p) / 100.0));
        }
    }

    vector<double> partVert(bombCondVert.size()), partHor(bombCondHor.size());
    
    
    double total = 0;
    for (int i = 0; i < bombCondHor.size(); ++i)
    {
        total += bombCondHor[i].second;
        partHor[i] = total;
    }
    
    total = 0;
    for (int i = 0; i < bombCondVert.size(); ++i)
    {
        total += bombCondVert[i].second;
        partVert[i] = total;
    }
    double res = 0.0;
    for (auto& p : platoons)
    {
        int w = p.x2 - p.x1 + 1;
        int h = p.y2 - p.y1 + 1;

        int firstV = search(bombCondVert, p.x1);
        int lastV = search(bombCondVert, p.x2);
        double probV = 0;
        if (lastV >= 0) probV += partVert[lastV];
        if (firstV >= 0 && bombCondVert[firstV].first == p.x1) firstV--;
        if (firstV >= 0) probV -= partVert[firstV];

        int firstH = search(bombCondHor, p.y1);
        int lastH = search(bombCondHor, p.y2);
        double probH = 0;
        if (lastH >= 0) probH += partHor[lastH];
        if (firstH >= 0 && bombCondHor[firstH].first == p.y1) firstH--;
        if (firstH >= 0) probH -= partHor[firstH];
        res += w * probH + h * probV - probH * probV;
    }


    printf("%.11lf", res);
    
    return 0;
}