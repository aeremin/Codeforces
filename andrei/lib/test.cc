#include <gtest/gtest.h>


int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    // TODO: set library_tests__enable_checks from command line flags, add launch script
    // TODO: runs tests without -DLOCAL_PC
    return RUN_ALL_TESTS();
}
