#include "gtest/gtest.h"
#include <cstddef>

// clang-format off

// https://youtu.be/jyYys1UcHkM?t=4444
// Тритами называются цифры сбалансированной системы счисления
// по основанию 3. Т.е. {-1, 0, 1}. Обозначим -1 как j.
// Написать функцию вычисления в compile-time.
// [TODO] написать также для вещественных чисел: 11j0.jj = 32 + 5/9

template <typename T = int>
consteval T ct_trit(const char* str)
{
    T result = 0;

    for (size_t i = 0; str[i] != '\0'; ++i)
    {
        char ch = str[i];

        switch (ch)
        {
        case '0': result *= 3; break;
        case '1': result = result * 3 + 1; break;
        case 'j': result = result * 3 - 1; break;
        default: throw "Only ['0','1','j'] symbols may be used";
        }
    }

    return result;
}


TEST(ct_trit, basic)
{
    EXPECT_EQ(ct_trit("0"), 0);
    EXPECT_EQ(ct_trit("1"), 1);
    EXPECT_EQ(ct_trit("10"), 3);
    EXPECT_EQ(ct_trit("100"), 9);
    EXPECT_EQ(ct_trit("j"), -1);
    EXPECT_EQ(ct_trit("j0"), -3);
    EXPECT_EQ(ct_trit("j00"), -9);
    EXPECT_EQ(ct_trit("10j"), 8);
    EXPECT_EQ(ct_trit("111"), 13);
}