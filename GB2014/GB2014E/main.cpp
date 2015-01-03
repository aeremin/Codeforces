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

struct Point
{
    int64_t x;
    int dif;
    int dominoInd;
};

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    int nDominoes;
    cin >> nDominoes;

    vector<Point>  points;

    for (int i = 0; i < nDominoes; ++i)
    {
        int64_t x, dx;
        cin >> x >> dx;
        Point left = { x, 1, i };
        points.push_back(left);
        Point right = { x + dx, -1, -1 };
        points.push_back(right);
    }
    
    sort(begin(points), end(points), [](Point a, Point b)
    {
        return a.x < b.x;
    });

    vector<int> dominoIndToPointInd(nDominoes);
    vector<Point> condensedPoints;
    int sumDif = 0;
    for (auto iter = begin(points); iter != end(points); ++iter)
    {
        sumDif += (*iter).dif;
        if (iter == begin(points) || (*iter).x > (*(iter - 1)).x)
        {
            Point point = { (*iter).x, sumDif, -1 };
            condensedPoints.push_back(point);
        }
        else
        {
            condensedPoints.back().dif = sumDif;
        }

        if ((*iter).dominoInd >= 0)
            dominoIndToPointInd[(*iter).dominoInd] = condensedPoints.size() - 1;
    }

    vector<int64_t> gapFromPrev;
    sumDif = 0;
    int64_t lastCoveredX = 0;
    for (auto iter = begin(condensedPoints); iter != end(condensedPoints); ++iter)
    {
        if (sumDif == 0)
            gapFromPrev.push_back((*iter).x - lastCoveredX);
        else
            gapFromPrev.push_back(0);
        sumDif = (*iter).dif;
        if (sumDif == 0)
            lastCoveredX = (*iter).x;
    }

    partial_sum(begin(gapFromPrev), end(gapFromPrev), begin(gapFromPrev));

    int nQueries;
    cin >> nQueries;

    for (int i = 0; i < nQueries; ++i)
    {
        int from, to;
        cin >> from >> to;
        cout << gapFromPrev[dominoIndToPointInd[to - 1]] - gapFromPrev[dominoIndToPointInd[from - 1]] << endl;
    }

    return 0;
}