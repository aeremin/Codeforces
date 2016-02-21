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

#include <algorithm>
#include <inttypes.h>
#include <iostream>
#include <vector>



// From algo/io/baseio.hpp


template<typename T> T read()
{
    T res;
    std::cin >> res;
    return res;
}

template<typename T> void print(const T& t)
{
    std::cout << t;
}

#ifndef LOCAL_PC
#define DEFINE_SIMPLE_READ_AND_PRINT(TYPE_NAME, FORMAT)  \
  template<>  \
  TYPE_NAME read<TYPE_NAME>() {  \
    TYPE_NAME res;  \
    scanf(FORMAT, &res); \
    return res; \
  }\
\
  template<>  \
  void print<TYPE_NAME>(const TYPE_NAME& t) {  \
    printf(FORMAT, t); \
  }\

DEFINE_SIMPLE_READ_AND_PRINT(int, "%d");
DEFINE_SIMPLE_READ_AND_PRINT(unsigned int, "%u");
DEFINE_SIMPLE_READ_AND_PRINT(int64_t, "%lld");
DEFINE_SIMPLE_READ_AND_PRINT(float, "%f");
DEFINE_SIMPLE_READ_AND_PRINT(double, "%lf");
DEFINE_SIMPLE_READ_AND_PRINT(char, "%c");

#endif


// From algo/io/readvector.hpp


template<typename T>
std::vector<T> readVector(size_t size)
{
    std::vector<T> res(size);
    for (auto& elt : res)
        elt = read<T>();
    return res;
}


// From iter/range.h

// Range-based style iteration helpers.
//
// * range(end)
//   Iterates over [0, end), e.g.:
//   ` for (auto i : range(5)) {
//   `     print(i);
//   ` }
//   prints "0 1 2 3 4"
//
// * range(begin, end)
//   Iterates over [begin, end), e.g.:
//   ` for (auto i : range(5, 10)) {
//   `     print(i);
//   ` }
//   prints "5 6 7 8 9"
//
// * FOR_TIMES(n)
//   Repeats loop body n times, e.g.:
//   ` print("We all live in a");
//   ` FOR_TIMES(3) {
//   `     print(" yellow submarine");
//   ` }




namespace internal {

    template<typename ValueT>
    class IterableRange {
    public:
        class iterator {
        public:
            iterator(ValueT v__) : v_(v__) {}

            iterator& operator++() { ++v_; return *this; }

            bool operator==(iterator rhs) const { return v_ == rhs.v_; }
            bool operator!=(iterator rhs) const { return v_ != rhs.v_; }

            ValueT operator*() const  { return v_; }
            ValueT operator->() const { return v_; }

        private:
            ValueT v_ = {};
        };

        IterableRange(ValueT begin__, ValueT end__) : begin_value_(std::min(begin__, end__)), end_value_(end__) {}

        iterator begin() const { return {begin_value_}; }
        iterator end() const { return {end_value_}; }

    private:
        ValueT begin_value_ = {};
        ValueT end_value_ = {};
    };

}  // namespace internal


template<typename ValueT>
internal::IterableRange<ValueT> range(ValueT end) {
    return {{}, end};
}

template<typename ValueT>
internal::IterableRange<ValueT> range(ValueT begin, ValueT end) {
    return {begin, end};
}

#define FOR_TIMES(N_TIMES) \
for (auto __counter = (N_TIMES); __counter > 0; --__counter)


// From Solvers/6xx/629/Solver629A.cpp

using namespace std;

class Solver629A
{
public:
    void run();
};

void Solver629A::run()
{
    int n;
    cin >> n;
    auto field = readVector<string>(n);
    vector<int> r(n, 0), c(n, 0);
    for (int i : range(n))
        for(int j : range(n))
            if (field[i][j] =='C'){
                r[i]++;
                c[j]++;
            }
    int ans = 0;
    for (auto elt : r)
        ans += elt * (elt - 1) / 2;

    for (auto elt : c)
        ans += elt * (elt - 1) / 2;

    cout << ans;
}


int main() {
    Solver629A solver;
    solver.run();
}

