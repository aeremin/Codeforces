#include <iostream>
#include <vector>
#include <deque>
#include <cassert>
#include <string>
#include <algorithm>


using namespace std;

int main()
{
#ifndef ONLINE_JUDGE  
	freopen("input.txt", "rt", stdin);
	freopen("output.txt", "wt", stdout);
#endif

	string s;
	cin >> s;
	int numLeft = 0;
	int numRight = 0;
	int numSharp = 0;

	vector<int> balance;
	int lastSharp = 0;
	for (int i = 0; i < s.length(); ++i)
	{
		switch (s[i])
		{
		case '(': numLeft++; break;
		case ')': numRight++; break;
		case '#': numSharp++; lastSharp = i;  break;
		}
		balance.push_back(numLeft - numRight - numSharp);
	}

	if (any_of(begin(balance), end(balance), [](int bal){ return bal < 0; }))
	{
		cout << -1;
		return 0;
	}

	for (int i = lastSharp; i < balance.size(); ++i)
	{
		if (balance[i] < balance.back())
		{
			cout << -1;
			return 0;
		}
	}

	for (int i = 0; i < numSharp - 1; ++i)
	{
		cout << 1 << '\n';
	}
	cout << 1 + balance.back();

	return 0;
}