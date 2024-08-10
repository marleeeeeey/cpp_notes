#include <gtest/gtest.h>

// clang-format off

template <typename T = double>  // Defaults for type
double foo(T x = 1.5)           // Defaults for value
{
    return x;
}

TEST(deduce, context)
{
    double v0 = foo(2.0);
    EXPECT_EQ(v0, 2.0);
    double v1 = foo<int>();
    EXPECT_EQ(v1, 1);
    double v2 = foo(); // <=== works well with default for type and value
    EXPECT_EQ(v2, 1.5);
}