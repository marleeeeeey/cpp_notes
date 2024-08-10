#include "gtest/gtest.h"
#include <concepts>

#if 0
template <typename T> int foo(T x) { return x; }
template <class T> int foo(T x) { return x + 1; }
#endif

template <std::integral T>
int foo(T x)
{
    return x % 2;
}

TEST(conceptform, basic)
{
    EXPECT_EQ(foo(11), 1);
}

#if 0
TEST(conceptform, err) {
  EXPECT_EQ(foo(0.0), 2);
}
#endif