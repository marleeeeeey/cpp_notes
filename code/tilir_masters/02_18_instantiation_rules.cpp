#include "gtest/gtest.h"

#define EARLY 0
#define SPECIALIZE 1

// clang-format off

template <typename T> T max(T x, T y) { return x > y ? x : y; }

#if (EARLY == 1)
extern template int max<int>(int, int); // error: explicit specialization of 'max<int>' after instantiation
#endif

#if (SPECIALIZE == 1)
template <> int max<int>(int x, int y) { return x > y ? x : y; } // <===
#endif

#if (EARLY == 0)
extern template int max<int>(int, int);
#endif

TEST(max_test_case, testWillPass)
{
    EXPECT_EQ(max(2, 11), 11);
}