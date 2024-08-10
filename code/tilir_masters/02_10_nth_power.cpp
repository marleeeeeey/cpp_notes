#include "gtest/gtest.h"
#include <concepts>

// Алгоритм быстрого возведения в степень (exponentiation by squaring).
// Быстрое возведение в степень имеет временную сложность O(log n).
// x^n = возвести (x^2) несколько раз пока (n=n/2) не станет равно 0.
unsigned nth_power(unsigned x, unsigned n)
{
    unsigned acc = 1; // Нейтральный элемент для умножения
    if ((x < 2) || (n == 1))
        return x;
    while (n > 0)
    {
        if ((n & 0x1) == 0x1) // Если нечетный
        {
            acc *= x;
            n -= 1;
        }
        x *= x;
        n /= 2;
    }
    return acc;
}

unsigned naive_nth_power(unsigned x, unsigned n)
{
    unsigned acc = 1;
    if ((x < 2) || (n == 1))
        return x;
    for (unsigned k = 0; k < n; ++k)
        acc *= x;
    return acc;
}

TEST(nthpower_test_case, testWillPass)
{
    EXPECT_EQ(nth_power(0, 10), 0);
    EXPECT_EQ(nth_power(1, 11), 1);
    EXPECT_EQ(nth_power(2, 8), (1 << 8));
    EXPECT_EQ(nth_power(2, 11), (1 << 11));
    EXPECT_EQ(nth_power(3, 0), 1);
    EXPECT_EQ(nth_power(3, 3), 27);
    EXPECT_EQ(nth_power(3, 15), 14348907);
    for (int x = 0; x < 10; ++x)
        for (int p = 0; p < 10; ++p)
            EXPECT_EQ(nth_power(x, p), naive_nth_power(x, p));
}
