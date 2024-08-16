#include "gtest/gtest.h"

// clang-format off

#define ENABLE_FAILS 0

// compile time only
consteval int ctsqr(int n)
{
    return n * n;
}

// OK, global constinit
constinit int g = ctsqr(100);

TEST(cexpr, cevinit)
{
    constexpr int c = ctsqr(100);

#if ENABLE_FAILS
    // FAIL: cannot assign constexpr (i.e. const) variable
    c += 1;
#endif

#if ENABLE_FAILS
    // FAIL: function consteval, x not CT known
    int x = 100;
    int y = ctsqr(x);
#endif

#if ENABLE_FAILS
    // FAIL: constinit can not be local
    constinit int d = ctsqr(100);           // <=== Невозможно создать локальную constinit переменную
#endif

    // OK to do this in runtime
    g += 1;

    EXPECT_EQ(g, 10001);
}