#include <gtest/gtest.h>
#include "CodeFuser.h"
#include <regex>

int main(int argc, char *argv[])
{
    for ( int i = 0; i < argc; ++i )
    {
        const std::string expectedFilterString( "--gtest_filter=*????*" );
        std::string arg = argv[i];
        if ( arg.substr( 0, 16 ) == expectedFilterString.substr( 0, 16 ) && arg.length() == expectedFilterString.length() )
        {
            auto problemName = arg.substr( 16, 4 );
            CodeFuser( problemName ).fuse();
        }
    }
    
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}