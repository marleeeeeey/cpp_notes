#include "gtest/gtest.h"
#include <cstddef>

// clang-format off

// https://youtu.be/jyYys1UcHkM?t=4630
// Написать вычисление длины массива времени компиляции.

template <typename T, size_t SZ>
consteval size_t arraySize(const T(&)[SZ])
{
    return SZ;
}


TEST(ct_trit, basic)
{
    EXPECT_EQ(arraySize({1,2,3}), 3);
    EXPECT_EQ(arraySize({1}), 1);
    EXPECT_EQ(arraySize("hello"), 6);
}