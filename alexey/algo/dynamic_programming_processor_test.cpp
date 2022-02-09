#include <gtest/gtest.h>
#include "algo/dynamic_programming_processor.h"

TEST( DPProcessorTest, CheapestSwitch )
{
    enum State {First, Second};
    DPProcessor<int, int, 2> dpprocessor;
    dpprocessor
        .addRule(State::First, State::Second,  [](int a) {return a;})
        .addRule(State::First, State::First,   [](int) {return 0;})
        .addRule(State::Second, State::Second, [](int) {return 0;});
    std::vector<int> input = { 103, 20, 25, 55, 11, 100, 1000 };
    auto res = dpprocessor.process( { 0, 1000 }, input.begin(), input.end() );
    std::vector<int> expected = { 0, 11 };
    EXPECT_EQ( expected, res );
}