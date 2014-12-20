#include <iostream>
#include <vector>
#include <deque>
#include <cassert>

using namespace std;

int main()
{
#ifndef ONLINE_JUDGE  
  freopen("input.txt", "rt", stdin);
  freopen("output.txt", "wt", stdout);
#endif
  int n, m;
  cin >> n >> m;
  
  vector<vector<char>> table;
  vector<bool> canbreak(m, false);

  for (int i = 0; i < n; ++i)
  {
    table.push_back(vector<char>( m ) );
    for (int j = 0; j < m; ++j)
    {
      cin >> table[i][j];
    }
  }

  int todel = 0;
  for (int j = 0; j < m; ++j)
  {
    bool needdel = false;
    
    vector<int> breaks;

    char cur = 'a';
    for (int i = 0; i < n; ++i)
    {
      if (canbreak[i])
      {
        cur = 'a';
      }

      if (table[i][j] < cur)
      {
        needdel = true;
        break;
      }

      if (table[i][j] > cur)
      {
        breaks.push_back( i );
      }

      cur = table[i][j];
    }

    if (needdel) todel++;
    else     for (int k = 0; k < breaks.size(); ++k) canbreak[breaks[k]] = true;
  }

  cout << todel;
  return 0;
}