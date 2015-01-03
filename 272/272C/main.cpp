
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

string str, pattern;

vector<int> endOfPattern;

void improve(int& value, int cand)
{
    value = max(value, cand);
}

int main()
{
#ifndef ONLINE_JUDGE  
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif


    cin >> str >> pattern;

    vector<vector<int>> answer(str.length() + 1, vector<int>(str.length() + 1, 0));

    for (int i = 0; i < str.length(); ++i)
    {
        int patternPos = 0;
        int strpos;
        for (strpos = i; strpos < str.length(); ++strpos)
        {
            if (str[strpos] == pattern[patternPos])
            {
                patternPos++;
                if (patternPos == pattern.length())
                    break;
            }
        }
        endOfPattern.push_back(strpos < str.length() ? strpos : -1);
    }

    for (int right = 0; right < str.length(); ++right)
    {
        for (int removed = 0; removed <= right; ++removed)
        {
            improve(answer[right + 1][removed], answer[right][removed]);
            improve(answer[right + 1][removed + 1], answer[right][removed]);
            if (endOfPattern[right] != -1)
                improve(answer[endOfPattern[right] + 1][removed + endOfPattern[right] - right - pattern.length() + 1], answer[right][removed] + 1);
        }
    }

    for (int elt : answer.back())
        cout << elt << ' ';

    return 0;
}