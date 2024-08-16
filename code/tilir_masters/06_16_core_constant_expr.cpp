#include "gtest/gtest.h"

// clang-format off

struct S
{
    int n_;
    S(int n) : n_(n) {}     // <===  non-constexpr ctor!
    constexpr int get() { return 42; }
};

TEST(cexpr, cce)
{
    S s{2};
    constexpr int k =
        s.get();            // <=== Core Constant Expression
    EXPECT_EQ(k, 42);
}