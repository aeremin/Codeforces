#include <iostream>
#include <vector>
#include <deque>
#include <cassert>
#include <algorithm>

using namespace std;

int tableWidth, tableHeight;
int blockHeight;

struct Place
{
  int x, y;
  int ind() const { return x + ((tableWidth + 2) * y);  }
  bool isFinal() const { return (x <= 0) || (y <= 0) || (x == tableWidth + 1); }
  void apply(char c)
  {
    switch(c)
    {
    case '<':
      x--;
      break;
    case '>':
      x++;
      break;
    case '^':
      y--;
      break;
    }
  }
  int block() const { return ((y - 1) / blockHeight) + 1; }
};

struct Query
{
  char type;
  Place place;
  char dir;
};


vector<char> table;
vector<Place> to;
vector<Query> queries;

void update(const Place from)
{
  Place cur = from;
  bool lost = false;
  char dir = ' ';
  char prevDir = ' ';
  int timeout = 0;
  while (!cur.isFinal() && cur.y == from.y && !lost)
  {
    dir = table[cur.ind()];
    lost = (dir == '<' && prevDir == '>') || (dir == '>' && prevDir == '<');
    cur.apply( dir );
    prevDir = dir;
    assert(timeout ++ < tableWidth + 1);
  }
  
  if (lost)
  {
    cur.x = -1; cur.y = -1;
    to[from.ind()] = cur;
  }
  else if (cur.isFinal())
  {
    to[from.ind()] = cur;
  }
  else if (cur.block() == from.block())
  {
    to[from.ind()] = to[cur.ind()];
  }
  else
  {
    to[from.ind()] = cur;
  }
}

void generateTestCase( int width, int height )
{
  int nQeries = 1e5;
  cout << height << ' ' << width << ' ' << nQeries << endl;
  Place cur;
  for (cur.y = 1; cur.y <= height; cur.y++)
  {
    for (cur.x = 1; cur.x <= width; cur.x++)
      cout << '^';
    cout << endl;
  }

  for (int i = 0; 2 * i < nQeries; ++i)
  {
    cout << 'A' << ' ' << height << ' ' << nQeries % width + 1 << endl;
    int x = rand() % width + 1;
    int y = rand() % height + 1;
    char dir = rand() % 2 ? '<' : '>';
    cout << 'C' << ' ' << y << ' ' << x << ' ' << dir << endl;
  }
}

int main()
{
#ifndef ONLINE_JUDGE  
  freopen("input.txt", "rt", stdin);
  freopen("output.txt", "wt", stdout);
#endif
  
  //generateTestCase( 10, 1e5 ); return 0;
  
  int nQueries;
  cin >> tableHeight >> tableWidth >> nQueries;

  //blockHeight = sqrt( float( tableHeight) );

  int maxInd = (tableWidth + 2) * (tableHeight + 1);
  table.resize(maxInd);

  Place cur;
  for (cur.y = 1; cur.y <= tableHeight; cur.y++)
    for (cur.x = 1; cur.x <= tableWidth; cur.x++)
      cin >> table[cur.ind()];
  
  to.resize(maxInd);

  int aQueries = 0;
  int cQueries = 0;
  for (int iQuery = 0; iQuery < nQueries; ++iQuery)
  {
    Query q;
    cin >> q.type >> q.place.y >> q.place.x;
    if (q.type == 'A')
    {
      aQueries ++;
    }
    else
    {
      cQueries ++;
      cin >> q.dir;
    }
    queries.push_back( q );
  }

  blockHeight = max(sqrt( (double(aQueries) * tableHeight )/ (cQueries * tableWidth * 5)), 1.1);

  for (cur.y = 1; cur.y <= tableHeight; cur.y++)
    for (cur.x = 1; cur.x <= tableWidth; cur.x++)
      update(cur);

  for (int iQuery = 0; iQuery < nQueries; ++iQuery)
  {
    Query& q = queries[iQuery];
    cur = q.place;
    if (q.type == 'A')
    {
      while (!cur.isFinal()) cur = to[cur.ind()];
      cout << cur.y << " " << cur.x << "\n";
    }
    else
    {
      table[cur.ind()] = q.dir;
      int minHeight = cur.y;
      int maxHeight = min( cur.block() * blockHeight, tableHeight );
      Place upd;
      for (upd.y = minHeight; upd.y <= maxHeight; ++upd.y)
        for (upd.x = 1; upd.x <= tableWidth; ++upd.x)
          update(upd);
    }

  }
    
  return 0;
}