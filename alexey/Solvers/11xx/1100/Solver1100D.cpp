#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
#include "util/relax.h"
#include "algo/geometry/geomvector.h"
#include "algo/io/readvector.h"
#include "math/sign.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1100/problem/D
class Solver1100D {
public:
    void run();

    vector<GeomVector2I> rooks;
    GeomVector2I king;

    // Returns true if final position is achieved
    bool GoTo(const GeomVector2I& pos);

    bool IsRookAt(const GeomVector2I& pos) const;
};

void Solver1100D::run() {
    king = read<GeomVector2I>();
    rooks = readVector<GeomVector2I>(666);

    if (!GoTo({ 500, 500 }))
        return;

    int A = 0, B = 0, C = 0, D = 0;
    for (auto l : rooks) {
        if (l[0] < 500 && l[1] < 500) ++A;
        if (l[0] > 500 && l[1] < 500) ++B;
        if (l[0] > 500 && l[1] > 500) ++C;
        if (l[0] < 500 && l[1] > 500) ++D;
    }

    int M = min({ A, B, C, D });
    GeomVector2I dir;
    if (M == A) {
        GoTo({ 999, 999 });
    }
    else if (M == B) {
        GoTo({ 0, 999 });
    }
    else if (M == C) {
        GoTo({ 0,   0 });
    }
    else {
        assert(M == D);
        GoTo({ 999,   0 });
    }
}

bool Solver1100D::GoTo(const GeomVector2I & pos)
{
    while (!(king == pos)) {
        auto dirGlobal = pos - king;
        king += { sgn(dirGlobal[0]), sgn(dirGlobal[1]) };
        if (IsRookAt(king)) {
            // There is no rook here: in another case,
            // we would have already won on previous turn.
            // But we will win on this turn.
            king -= { sgn(dirGlobal[0]), 0 };
        }

        cout << king << endl;
        auto k = read<int>();
        auto mov = read<GeomVector2I>();
        if (k <= 0) return false;
        rooks[k - 1] = mov;
    }
    return true;
}

bool Solver1100D::IsRookAt(const GeomVector2I & pos) const
{
    return count(begin(rooks), end(rooks), pos);
}

class Solver1100DTest : public ProblemTest {};
