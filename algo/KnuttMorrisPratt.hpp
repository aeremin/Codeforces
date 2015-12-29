#pragma once
#include <string>
#include <vector>
using std::string;
using std::vector;

inline vector<int> calc_prefix_function(const string& s)
{
	vector<int> pi;
	if (s.empty())
		return pi;
	pi.push_back(0);
	for (int i = 1; i < s.length(); ++i)
	{
		int curPi = pi.back();
		while (curPi > 0 && s[i] != s[curPi])
			curPi = pi[curPi - 1];
		if (s[i] == s[curPi]) curPi++;
		pi.push_back(curPi);
	}
	return pi;
}