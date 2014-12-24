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

vector<int64_t> primes;
vector<vector<int>> powers;
vector<int64_t> numbers;


vector <vector<int>> g;
vector<int> mt;
vector<char> used;

bool try_kuhn(int v) {
    if (used[v])  return false;
    used[v] = true;
    for (size_t i = 0; i<g[v].size(); ++i) {
        int to = g[v][i];
        if (mt[to] == -1 || try_kuhn(mt[to])) {
            mt[to] = v;
            return true;
        }
    }
    return false;
}


void extractprimes(int index)
{
    auto a = numbers[index];
    powers.push_back(vector<int>(primes.size(), 0));
    for (int i = 0; i < primes.size(); ++i)
    {
        int p = primes[i];
        int deg = 0;
        while (a % p == 0)
        {
            a /= p;
            powers[index][i]++;
        }
    }

    for (int64_t d = 2; d * d <= a; ++d)
    {
        if (a % d == 0)
        {
            primes.push_back(d);
            a = a / d;
            powers[index].push_back(1);
            while (a % d == 0)
            {
                a = a / d;
                powers[index].back()++;
            }
        }
    }

    if (a > 1)
    {
        primes.push_back(a);
        powers[index].push_back(1);
    }
}

int main()
{
#ifndef ONLINE_JUDGE  
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    int n, m;
    cin >> n >> m;
    numbers.resize(n);
    for (int i = 0; i < n; ++i)
    {
        int64_t elt;
        cin >> elt;
        numbers[i] = elt;
        extractprimes(i);
    }

    vector<pair<int, int>> edges;
    for (int i = 0; i < m; ++i)
    {
        int a, b;
        cin >> a >> b;
        a--; b--;
        if (a % 2 == 1) swap(a, b);
        edges.push_back(make_pair(a, b));
    }

    int result = 0;
    for (int iPrime = 0; iPrime < primes.size(); ++iPrime)
    {
        g.clear();
        mt.clear();
        used.clear();
        
        vector<int> startDecomposedL;
        vector<int> endDecomposedL;
        int totalL = 0;
        for (int iNum = 0; iNum < numbers.size(); iNum += 2)
        {
            int deg = (powers[iNum].size() > iPrime) ? powers[iNum][iPrime] : 0;
            startDecomposedL.push_back(totalL);
            totalL += deg;
            endDecomposedL.push_back(totalL);
        }

        vector<int> startDecomposedR;
        vector<int> endDecomposedR;
        int totalR = 0;
        for (int iNum = 1; iNum < numbers.size(); iNum += 2)
        {
            int deg = (powers[iNum].size() > iPrime) ? powers[iNum][iPrime] : 0;
            startDecomposedR.push_back(totalR);
            totalR += deg;
            endDecomposedR.push_back(totalR);
        }

        g.resize(totalL);
        
        for (auto edge : edges)
        {
            for (int iDecL = startDecomposedL[edge.first / 2]; iDecL < endDecomposedL[edge.first / 2]; ++iDecL)
                for (int iDecR = startDecomposedR[edge.second / 2]; iDecR < endDecomposedR[edge.second / 2]; ++iDecR)
                    g[iDecL].push_back(iDecR);
        }

        mt.assign(totalR, -1);
        for (int v = 0; v < totalL; ++v) {
            used.assign(totalL, false);
            if (try_kuhn(v)) result++;
        }
    }

    cout << result;

    return 0;
}
