#include <Solvers/pch.h>
#include "algo/io/baseio.hpp"
#include "iter/range.h"
#include "algo/numbertheory/Residue.hpp"
#include "math/quick_power.h"
#include "algo/updatetypes/MultiplyBy.hpp"
#include "algo/updateappliers/MultiplyByApplier.h"
#include "algo/SegmentTree.hpp"

using namespace std;

struct Matrix2x2 {
    CodeforcesResidue64 a00, a01, a10, a11;
    
    Matrix2x2(CodeforcesResidue64 b00, CodeforcesResidue64 b01,
              CodeforcesResidue64 b10, CodeforcesResidue64 b11) : a00(b00), a01(b01), a10(b10), a11(b11) {}
    Matrix2x2() : a00(1), a01(0), a10(0), a11(1) {}
    Matrix2x2(int) : a00(1), a01(0), a10(0), a11(1) {}
    friend Matrix2x2 operator*(const Matrix2x2& lh, const Matrix2x2& rh) {
        return{ lh.a00 * rh.a00 + lh.a01 * rh.a10,
            lh.a00 * rh.a01 + lh.a01 * rh.a11,
            lh.a10 * rh.a00 + lh.a11 * rh.a10,
            lh.a10 * rh.a01 + lh.a11 * rh.a11 };
    }

    friend Matrix2x2 operator+(const Matrix2x2& lh, const Matrix2x2& rh) {
        return{ lh.a00 + rh.a00,
            lh.a01 + rh.a01,
            lh.a10 + rh.a10,
            lh.a11 + rh.a11, };
    }
};

class Solver718C {
public:
    void run();
};

void Solver718C::run() {
    int n, m;
    cin >> n >> m;
    const Matrix2x2 start = { 1, 0, 0, 0 };
    const Matrix2x2 mult = { 1, 1, 1, 0 };
    const Matrix2x2 one;
    vector<Matrix2x2> data(n, start);
    auto st = makeSegmentTree(data, std::plus<Matrix2x2>(), updateTypes::MultiplyBy<Matrix2x2>(one));

    for (int i = 0; i < n; ++i) {
        int64_t a;
        cin >> a;
        st.updateElement(i, quick_power(mult, a - 1, one));
    }

    for (int i = 0; i < m; ++i) {
        int t, l, r;
        cin >> t >> l >> r;
        --l;
        if (t == 1) {
            int x;
            cin >> x;
            st.updateRange(l, r, quick_power(mult, x, one));
        }
        else {
            cout << st.getValueOnSegment(l, r).a00 << "\n";
        }
    }
}


class Solver718CTest : public ProblemTest {};


TEST_F(Solver718CTest, Example1) {
    string input = R"(5 4
1 1 2 1 1
2 1 5
1 2 4 2
2 2 4
2 1 5
)";
    string output = R"(5
7
9
)";
    setInput(input);
    Solver718C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

