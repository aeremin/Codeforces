#include <iostream>
#include <cassert>
#include "../algo/SlidingWindowMinFinder.h"

using namespace std;

class A
{};

class B
{
public:
	B(A a) {}
};

void foo(B b){ cout << "foo(B)"; }

void foo(A a){ cout << "foo(A)"; }

bool testSlidingWindowMinFinder()
{
  vector<int> data;
  data.push_back(  2 );
  data.push_back(  3 );
  data.push_back(  3 );
  data.push_back(  3 );
  data.push_back(  1 );
  data.push_back(  5 );
  data.push_back( -2 );
  data.push_back(  2 );
  data.push_back(  7 );
    
  SlidingWindowMinFinder<int> minFinder(data);
  minFinder.incRight(); // 2
  minFinder.incRight(); // 2 3
  assert( minFinder.getMin() == 2);
  minFinder.incLeft(); // 3
  assert( minFinder.getMin() == 3);
  minFinder.incRight(); // 3 3
  assert( minFinder.getMin() == 3);
  minFinder.incRight(); // 3 3 3
  assert( minFinder.getMin() == 3);
  minFinder.incLeft(); // 3 3
  assert( minFinder.getMin() == 3);
  minFinder.incLeft(); // 3
  assert( minFinder.getMin() == 3);
  minFinder.incRight(); // 3 1 
  minFinder.incRight(); // 3 1 5
  minFinder.incLeft(); // 1 5
  assert( minFinder.getMin() == 1);
  minFinder.incLeft(); // 5
  assert( minFinder.getMin() == 5);
  minFinder.incRight(); // 5 -2
  minFinder.incLeft(); // -2
  assert( minFinder.getMin() == -2);
  minFinder.incRight(); // -2 2
  minFinder.incRight(); // -2 2 7
  assert( minFinder.getMin() == -2);
  minFinder.incLeft(); // 2 7
  assert( minFinder.getMin() == 2);
  minFinder.incLeft(); // 7
  assert( minFinder.getMin() == 7);

  return true;
}



int main()
{	
  testSlidingWindowMinFinder();
  
  A a;
  B b(a);
  foo(a);
  foo(b);
  char c; cin >> c;
  return 0;
}



