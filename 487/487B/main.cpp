#include <iostream>
#include <vector>
#include <deque>

using namespace std;

template<class T>
class SlidingWindowMinFinder
{
private:
  vector<T>& data_;
  deque<pair<T, int>> currentSet_;
  int left_;
  int right_;

public:
  SlidingWindowMinFinder( vector<T>& data ) : data_( data ), left_(0), right_(0)
  {
    //currentSet_.push_back( make_pair<T, int>(data_.front(), 0) );
  }

  void incLeft()
  {
    left_++;
  }

  void incRight()
  {
    T newElt = data_[right_];
    while (!currentSet_.empty() && currentSet_.back().first >= newElt) currentSet_.pop_back();
    currentSet_.push_back( make_pair(newElt, right_) );
    right_++;
  }

  T getMin()
  {
    while (currentSet_.front().second < left_) currentSet_.pop_front();
    return currentSet_.front().first;
  }

  int getLeft()
  {
    return left_;
  }

  int getRight()
  {
    return right_;
  }

};

int main()
{
  int nNumbers, maxDif, minLen;
  cin >> nNumbers >> maxDif >> minLen;

  vector<int> tape, minustape;
  for (int i = 0; i < nNumbers; ++i)
  {
    int t;
    cin >> t;
    tape.push_back(t);
    minustape.push_back(-t);
  }

  SlidingWindowMinFinder<int> minFinder( tape );
  SlidingWindowMinFinder<int> maxFinder( minustape );

  vector<int> maxBack;
  int left = 0;
  for (int right = 0; right < nNumbers; ++right)
  {
    minFinder.incRight();
    maxFinder.incRight();

    int min =  minFinder.getMin();
    int max = -maxFinder.getMin();
    while (max - min > maxDif)
    {
      minFinder.incLeft();
      maxFinder.incLeft();
      left++;
      min =  minFinder.getMin();
      max = -maxFinder.getMin();
    }
    maxBack.push_back( right - left + 1 );
    //cout << maxBack.back() << endl;
  }

  vector<int> minParts;
  SlidingWindowMinFinder<int> resultFinder(minParts);

  for(int i = 0; i < nNumbers; ++i)
  {
    if (i + 1 < minLen)
    {
      minParts.push_back(INT_MAX);
      continue;
    }

    if (maxBack[i] == i + 1)
    {
      minParts.push_back(1);
      continue;
    }

    if (maxBack[i] < minLen)
    {
      minParts.push_back(INT_MAX);
      continue;
    }

    while (resultFinder.getLeft() < i - maxBack[i]) resultFinder.incLeft(); 
    while (resultFinder.getRight() <= i - minLen) resultFinder.incRight();
    int curMinParts = resultFinder.getMin();
    if (curMinParts < INT_MAX) curMinParts++;
    minParts.push_back( curMinParts );
  }
  
  if (minParts.back() < INT_MAX)
  {
    cout << minParts.back() << endl;
  }
  else
  {
    cout << -1 << endl;
  }

  return 0;
}
