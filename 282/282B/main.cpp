#include <iostream>
#include <vector>
#include <deque>
#include <cassert>
#include <string>
#include <cstdint>

using namespace std;

vector<int> prefix_function(const string& s) 
{
	int n = (int)s.length();
	vector<int> pi(n);
	for (int i = 1; i<n; ++i) {
		int j = pi[i - 1];
		while (j > 0 && s[i] != s[j])
			j = pi[j - 1];
		if (s[i] == s[j])  ++j;
		pi[i] = j;
	}
	return pi;
}

const int MODULO = 1e9 + 7;

int main()
{
#ifndef ONLINE_JUDGE  
	freopen("input.txt", "rt", stdin);
	freopen("output.txt", "wt", stdout);
#endif

	string s;
	string t;
	cin >> s;
	cin >> t;

	string concat = t + '$' + s;
	auto pi = prefix_function(concat);

	int goodpi = t.length();

	vector<int64_t> res;
	vector<int64_t> sumres;

	res.push_back(1);
	sumres.push_back(1);
	int lastStringStart = -1;

	for (int i = 0; i < s.length(); ++i)
	{
		if (pi[i + goodpi + 1] == goodpi) lastStringStart = i - goodpi + 1;
		int64_t curres = res.back();
		if (lastStringStart >= 0)
		{
			curres = (curres + sumres[lastStringStart]) % MODULO;
		}
		int64_t currsumres = (sumres.back() + curres) % MODULO;
		res.push_back(curres);
		sumres.push_back(currsumres);
	}

	cout << (res.back() + MODULO - 1) % MODULO;

	return 0;
}