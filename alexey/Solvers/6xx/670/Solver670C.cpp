#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/io/readvector.hpp"
#include "util/relax.h"
using namespace std;

class Solver670C {
public:
    void run();
};

void Solver670C::run() {
    int nScientists;
    cin >> nScientists;
    map<int, int> countOfLanguageKnowers;
    auto langs = readVector<int>(nScientists);
    for (auto l : langs)
        ++countOfLanguageKnowers[l];

    int nMovies;
    cin >> nMovies;

    auto langsSound = readVector<int>(nMovies);
    auto langsSubs = readVector<int>(nMovies);

    auto best = make_tuple( -1, -1, 0 );
    for (int i : range(nMovies))
        relax_max(best, make_tuple(countOfLanguageKnowers[langsSound[i]], countOfLanguageKnowers[langsSubs[i]], i + 1));

    cout << get<2>(best);
}


class Solver670CTest : public ProblemTest {};


TEST_F(Solver670CTest, Example1) {
    string input = R"(3
2 3 2
2
3 2
2 3
)";
    string output = R"(2
)";
    setInput(input);
    Solver670C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver670CTest, Example2) {
    string input = R"(6
6 3 1 1 3 7
5
1 2 3 4 5
2 3 4 5 1
)";
    string output = R"(3
)";
    setInput(input);
    Solver670C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

