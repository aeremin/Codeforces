// Increases stack size under GNU/Linux operating systems.
//
// You only need to *link* this file.

#include <iostream>

#include <sys/resource.h>

#include "util/check.h"


namespace {

#ifndef STACK_SIZE_MB
#   define STACK_SIZE_MB  2000
#endif

class StackEnlarger {
public:
    StackEnlarger() {
        constexpr rlim_t desired_stack_size = STACK_SIZE_MB * 1024 * 1024;
        rlimit rl;
        CHECK(getrlimit(RLIMIT_STACK, &rl) == 0);
        if (rl.rlim_cur < desired_stack_size) {
            rl.rlim_cur = desired_stack_size;
            CHECK(setrlimit(RLIMIT_STACK, &rl) == 0);
        }
    }
};

StackEnlarger stack_enlarger;

}  // namespace
