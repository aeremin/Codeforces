#include <iostream>
#include <vector>
#include <deque>
#include <cassert>
#include <string>
#include <algorithm>
#include <set>

using namespace std;

vector<int> numbers;
vector<int> numToIndex;

int nextJ(int currDividend, int currDivisor, int maxMod)
{
    int nextInterestingNum = (currDividend / currDivisor) * currDivisor - 1;
    return numToIndex[nextInterestingNum];
}

int main()
{
#ifndef ONLINE_JUDGE  
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif
    int nNumbers;
    cin >> nNumbers;

    numbers.resize(nNumbers);
    for (auto& num : numbers)
        cin >> num;
    
    sort(begin(numbers), end(numbers));
    auto last = unique(begin(numbers), end(numbers));
    numbers.erase(last, end(numbers));

    numToIndex.resize(numbers.back() + 1);
    for (int i = 0; i < numbers.size(); ++i)
        numToIndex[numbers[i]] = i;

    int currIndTo = 0;
    for (auto& elt : numToIndex)
    {
        if (elt == 0)
            elt = currIndTo;
        else
            currIndTo = elt;
    }

    int maxMod = 0;
    int i = numbers.size() - 1;
    for (i = numbers.size() - 1; i >= 0 && numbers[i] > maxMod - 1; --i)
    {
        int j = numbers.size() - 1;
        while (j > i)
        {
            maxMod = max(maxMod, numbers[j] % numbers[i]);
            j = nextJ(numbers[j], numbers[i], maxMod);
        }
    }
 
    cout << maxMod;
    return 0;
}