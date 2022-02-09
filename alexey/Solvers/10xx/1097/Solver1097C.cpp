#include <Solvers/pch.h>
#include "algo/io/baseio.h"
#include "iter/range.h"
#include "algo/io/readvector.h"
#include "util/relax.h"
#include "util/getters.h"
using namespace std;

// Solution for Codeforces problem http://codeforces.com/contest/1097/problem/C
class Solver1097C {
public:
    void run();
};

namespace {

struct SequenceProperties {
    int totalBalance = 0;
    bool canBeFirst = false;
    bool canBeLast = false;
};

struct BucketProperties {
    int canBeBoth = 0;
    int canBeOnlyFirst = 0;
    int canBeOnlyLast = 0;
};

SequenceProperties GetProperties(const string& s) {
    int a1 = 0;
    int b1 = 0;
    for (auto& c : s) {
        int b = (c == '(') ? +1 : -1;
        b1 += b;
        relax_min(a1, b1);
    }
    return { b1, a1 == 0, a1 - b1 == 0 };
}

}

void Solver1097C::run() {
    auto n = read<int>();
    auto seqs = readVector<string>(n);
    unordered_map<int, BucketProperties> buckets;
    for (const auto& s: seqs) {
        auto props = GetProperties(s);
        if (props.canBeFirst && props.canBeLast)
            buckets[props.totalBalance].canBeBoth++;
        else if (props.canBeFirst)
            buckets[props.totalBalance].canBeOnlyFirst++;
        else if (props.canBeLast)
            buckets[props.totalBalance].canBeOnlyLast++;
    }
    
    const auto const_buckets = move(buckets);

    int64_t ans = 0;
    for (const auto[b, props1] : const_buckets) {
        if (b < 0) continue;
        if (b == 0) {
            assert(props1.canBeOnlyFirst == 0);
            assert(props1.canBeOnlyLast == 0);
            ans += props1.canBeBoth / 2;
        }
        else {
            auto props2 = value_or(const_buckets, -b);
            assert(props1.canBeBoth == 0);
            assert(props2.canBeBoth == 0);
            ans += min(props1.canBeOnlyFirst, props2.canBeOnlyLast);
            ans += min(props1.canBeOnlyLast, props2.canBeOnlyFirst);
        }
    }

    cout << ans;
}


class Solver1097CTest : public ProblemTest {};


TEST_F(Solver1097CTest, Example1) {
    setInput(R"(
7
)())
)
((
((
(
)
)

)");
    string output = R"(
2

)";
    Solver1097C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1097CTest, Example2) {
    setInput(R"(
4
(
((
(((
(())

)");
    string output = R"(
0

)";
    Solver1097C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1097CTest, Example3) {
    setInput(R"(
2
(())
()

)");
    string output = R"(
1

)";
    Solver1097C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1097CTest, Example4) {
    setInput(R"(
5
(
((
(((
(())
(())
)");
    string output = R"(
1

)";
    Solver1097C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1097CTest, Example5) {
    setInput(R"(

2
(
)

)");
    string output = R"(
1

)";
    Solver1097C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1097CTest, Example6) {
    setInput(R"(

2
(
)
)
)

)");
    string output = R"(
1

)";
    Solver1097C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1097CTest, Example7) {
    setInput(R"(

8
(
(
(
)
)
)
)
)

)");
    string output = R"(
3

)";
    Solver1097C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1097CTest, Example8) {
    setInput(R"(

5
())(()
())(()
((()))
((()))
((()))

)");
    string output = R"(
1

)";
    Solver1097C().run();
    EXPECT_EQ_FUZZY(getOutput(), output);
}

TEST_F(Solver1097CTest, Randomized) {
    int n = 100000;
    stringstream ss;
    ss << n << "\n";

    for (int i : range(n)) {
        string s;
        for (int j : range(10)) {
            if (rand() % 2)
                s.push_back(')');
            else
                s.push_back('(');
        }
        ss << s << "\n";
    }

    setInput(ss.str());
    Solver1097C().run();
}

TEST_F(Solver1097CTest, Covering) {
    int n = 100000;
    stringstream ss;
    ss << n << "\n";

    for (int i : range(n)) {
        string s;
        for (int j : range(10)) {
            if ((i % (1 << 10)) & (1 << j))
                s.push_back(')');
            else
                s.push_back('(');
        }
        ss << s << "\n";
    }

    setInput(ss.str());
    Solver1097C().run();
}



TEST_F(Solver1097CTest, GetPropertiesTest) {
    SequenceProperties props;
    
    props = GetProperties("(((");
    EXPECT_EQ(props.totalBalance, 3);
    EXPECT_EQ(props.canBeFirst, true);
    EXPECT_EQ(props.canBeLast, false);

    props = GetProperties(")))");
    EXPECT_EQ(props.totalBalance, -3);
    EXPECT_EQ(props.canBeFirst, false);
    EXPECT_EQ(props.canBeLast, true);

    props = GetProperties("()))((((((");
    EXPECT_EQ(props.totalBalance, 4);
    EXPECT_EQ(props.canBeFirst, false);
    EXPECT_EQ(props.canBeLast, false);

    props = GetProperties("(()(()))");
    EXPECT_EQ(props.totalBalance, 0);
    EXPECT_EQ(props.canBeFirst, true);
    EXPECT_EQ(props.canBeLast, true);
}