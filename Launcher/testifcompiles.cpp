#include <vector>
#include <deque>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <numeric>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdint>
#include <functional>

using namespace std;

namespace main
{

class DummySolver
{
public:
    void run() {}
};



}
using CurrentSolver = main::DummySolver;

#ifdef ONLINE_JUDGE
int main()
#else
int main2()
#endif
{
    ios::sync_with_stdio( false );
    CurrentSolver().run();
	return 0;
}