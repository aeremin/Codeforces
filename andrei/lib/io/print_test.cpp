#include "io/print.h"

#include "internal_tests/io_redirection.h"
#include "solution_tests/matchers.h"
#include "std.h"


using PrintTest = TestWithIORedirection;

TEST_F(PrintTest, Basic) {
    print_ln(1.0);
    print_ln(1000.0);
    print_ln(1, 2);

    EXPECT_THAT(get_output(), EqualsTrimmed(R"(
1.000000000000
1000.000000000000
1 2
    )"));
}
