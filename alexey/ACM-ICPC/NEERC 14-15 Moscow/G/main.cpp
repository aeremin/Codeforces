#include <iostream>
#include <vector>
#include <deque>
#include <cassert>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <set>
#include <cstdint>
#include <limits>

using namespace std;

typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef vector<bool> vb;
typedef int64_t ll;

unordered_map<string, pair<string, int>> people;
vector<string> names;
vector<string> surnames;
vector<string> parents;

void parseLine(int iGuy)
{
    char inp[50];
    //scanf("%s", &inp);
    int i = 0;
    string surname, name, parent;
    string shit;
    cin >> surname;
    cin >> name;
    cin >> shit;
    cin >> shit;
    cin >> parent;
    people[name] = make_pair(surname, iGuy);
    names.push_back(name);
    surnames.push_back(surname);
    parents.push_back(parent);
}

vector<int> depth(1e5 + 1, -1);
vector<int> parInd(1e5 + 1, -1);
vector<int> used(1e5 + 1, false);
vector<int> timein(1e5 + 1, -1);

int cycleStop;
int timeCounter = 0;

int countDepth(int ind)
{
    if (parInd[ind] == -1)
    {
        used[ind] = true;
        timein[ind] = timeCounter++;
        depth[ind] = 1;
        return 1;
    }
    else if (depth[ind] > 0)
    {
        used[ind] = true;
        return depth[ind];
    }
    else if (used[ind])
    {
        cycleStop = ind;
        depth[ind] = timeCounter - timein[ind];
         return depth[ind];
    }
    else
    {
        used[ind] = true;
        timein[ind] = timeCounter++;
        depth[ind] = countDepth(parInd[ind]);
        if (cycleStop < 0) depth[ind]++;
        if (cycleStop == ind) cycleStop = -1;
        return depth[ind];
    }
}

int main()
{
    //freopen("problem.in", "rt", stdin);
    //freopen("problem.out", "wt", stdout);

    int nGuys;
    cin >> nGuys;

    for (int i = 0; i < nGuys; ++i) parseLine(i);

    for (int i = 0; i < nGuys; ++i)
    {
        auto parIt = people.find(parents[i]);
        if (parIt != people.end() && (*parIt).second.first == surnames[i] && (*parIt).second.second != i )
        {
            parInd[i] = (*parIt).second.second;
        }
    }

    for (int i = 0; i < nGuys; ++i)
    {
        cycleStop = -1;
        countDepth(i);
    }

    int res = -1;
    for (int i = 0; i < nGuys; ++i)
        res = max(res, depth[i]);

    cout << res;

    return 0;
}