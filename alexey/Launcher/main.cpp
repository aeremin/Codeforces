#include <gtest/gtest.h>
#include "CodeFuser.h"
#include <regex>

int main(int argc, char *argv[])
{
    for ( int i = 0; i < argc; ++i )
    {
        std::string arg = argv[i];
        auto problemName = GetProblemNameFromGtestFilter(arg);
        if (problemName.length()) {
            CodeFuser(problemName).fuse();
        }
    }
    
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}