#include "gtest/gtest.h"

// clang-format off

#define ENABLE_FAILS 0

template <typename... Ts>
auto sum_all(Ts... args)
{
    return (... + args); // error: unary fold expression has empty expansion for operator '+' with no fallback value
}

template <typename... Ts>
auto and_all(Ts... args)
{
    return (... && args); // OK => true
}

TEST(variadic, voidpack)
{
#if ENABLE_FAILS
    auto ires = sum_all();
    EXPECT_EQ(ires, 10);
#endif

    // unique case: only &&, || and comma can do this
    bool bres = and_all();
    EXPECT_EQ(bres, true);
}