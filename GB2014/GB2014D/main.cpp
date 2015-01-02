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

vector < vector<int> > g;
int nCities;

vector<int> color;

vector<int> time_in, time_out;
int dfs_timer = 0;

void dfs(int v) {
    time_in[v] = dfs_timer++;
    color[v] = 1;
    for (vector<int>::iterator i = g[v].begin(); i != g[v].end(); ++i)
        if (color[*i] == 0)
            dfs(*i);
    color[v] = 2;
    time_out[v] = dfs_timer++;
}

struct Road
{
    int from, to, len;
};

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    int nCities;
    cin >> nCities;
    g.resize(nCities);
    time_in.resize(nCities);
    time_out.resize(nCities);
    color.resize(nCities);

    vector<Road> roads;
    for (int i = 1; i < nCities; ++i)
    {
        Road road;
        cin >> road.from >> road.to >> road.len;
        roads.push_back(road);
        g[road.from - 1].push_back(road.to - 1);
        g[road.to - 1].push_back(road.from - 1);
    }

    dfs(0);

    vector<double> roadProb;

    double fullProb = double(nCities) * double(nCities - 1) * double(nCities - 2);
    
    for (int i = 0; i < roads.size(); ++i)
    {
        Road r = roads[i];
        int index1 = r.from - 1;
        int index2 = r.to - 1;
        int index;
        if (time_in[index1] > time_in[index2]) index = index1; else index = index2;
        double part1 = (time_out[index] - time_in[index]) / 2 + 1;
        double part2 = nCities - part1;

        double prob1 = max(0.0, part1 * (part1 - 1) * (part1 - 2));
        double prob2 = max(0.0, part2 * (part2 - 1) * (part2 - 2));
        
        roadProb.push_back(1 - (prob1 + prob2) / fullProb);
    }

    double ev = 0;
    for (int i = 0; i < roadProb.size(); ++i)
        ev += 2 * roads[i].len * roadProb[i];

    int nQueries;
    cin >> nQueries;
    for (int iQuery = 0; iQuery < nQueries; ++iQuery)
    {
        int roadInd, newLen;
        cin >> roadInd >> newLen;
        roadInd--;
        ev += 2 * roadProb[roadInd] * (newLen - roads[roadInd].len);
        roads[roadInd].len = newLen;
        printf("%.8lf\n", ev);
    }

    return 0;
}