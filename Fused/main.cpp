#include <vector>
#include <deque>
#include <queue>
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
#include <array>
#include <valarray>
#include <iomanip>
#include <cassert>
#include <memory>
#include <complex>
#include <regex>

using namespace std;


class SolverDummy
{
public:
    void run();
};

void SolverDummy::run()
{
}

using CurrentSolver = SolverDummy;
int main()
{
    ios::sync_with_stdio( false );
    CurrentSolver().run();
	return 0;
}
