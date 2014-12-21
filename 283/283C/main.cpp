#include <iostream>
#include <vector>
#include <deque>
#include <set>
#include <cassert>
#include <algorithm>

using namespace std;

struct Interval
{
  bool isSong;
  
  long long left;
  long long right;

  int times;
  int index;
};

bool canR( Interval actor, Interval song)
{
  return (actor.right >= song.right);
}

int getSingerIndex( Interval song, deque<Interval>& actors )
{
	if (actors.empty()) return -1;

	auto iter = lower_bound(begin(actors), begin(actors), song, [](Interval actor, Interval song) -> bool
	{
		return canR(actor, song);
	});

	//if (iter == end(actors))
}

int main()
{
#ifndef ONLINE_JUDGE  
  freopen("input.txt", "rt", stdin);
  freopen("output.txt", "wt", stdout);
#endif

  int nSongs;
  cin >> nSongs;
  vector<Interval> intervals;
  for (int i = 0; i < nSongs; ++i)
  {
    long long l, r;
    cin >> l >> r;
    Interval interval;
    interval.left = l;
    interval.right = r;
    interval.index = i;
	interval.isSong = true;
    intervals.push_back( interval );
  }

  int nActors;
  cin >> nActors;
  for (int i = 0; i < nActors; ++i)
  {
    long long c, l, r;
    cin >> l >> r >> c;
    Interval interval;
    interval.left = l;
    interval.right = r;
    interval.index = i;
    interval.times = c;
	interval.isSong = false;
    intervals.push_back( interval );
  }

  auto sortFun = [](Interval a, Interval b) -> bool
  {
	if (a.left < b.left) return true;
	if (a.left > b.left) return false;
	
	if (a.right > b.right) return true;
	if (a.right < b.right) return false;
	return (!a.isSong && b.isSong);
  };

  sort( begin(intervals), end(intervals), sortFun );
  
  auto orderRight = [](Interval a, Interval b) -> bool
  {
	  if (a.right < b.right) return true;
	  if (a.right > b.right) return false;
 	  
	  if (!a.isSong && b.isSong)  return false;
	  if (a.isSong && !b.isSong)  return true;
	  
	  return (a.index > b.index);
  };

  set<Interval, bool(*)(Interval, Interval)> actors( orderRight );
  vector<int> assignments( nSongs );
  vector<int> nAssignments(nActors, 0);
  
  for (auto cur : intervals)
  {
	  if (cur.isSong)
	  {
		  auto singer = actors.lower_bound(cur);
		  if (singer == end(actors))
		  {
			  cout << "NO\n";
			  return 0;
		  }
		  
		  nAssignments[(*singer).index]++;
		  assignments[cur.index] = (*singer).index + 1;
		  if (nAssignments[(*singer).index] == (*singer).times) actors.erase(singer);
	  }
	  else
	  {
		  actors.insert(cur);
	  }
  }

  cout << "YES\n";
  for (int i = 0; i < nSongs; ++i)
  {
	  cout << assignments[i] << ' ';
  }

  return 0;
}