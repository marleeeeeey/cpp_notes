#include <gtest/gtest.h>

// clang-format off

template <auto n> // <=== auto for type deduction
int foo() { return n; }

TEST(deduce, context)
{
    double v0 = foo<1>();
    EXPECT_EQ(v0, 1);
    double v1 = foo<2.0>();
    EXPECT_EQ(v1, 2);
}