#include "gtest/gtest.h"
#include <concepts>

#define ENABLE_FAILS 0

// Create a concept to check for the presence of a multiplication operation
template <typename T>
concept multiplacative = requires(T t) {
    { t *= t } -> std::convertible_to<T>;
#if ENABLE_FAILS
    { t.foo() }; // Error: because 'unsigned int' does not satisfy 'multiplacative'
#endif
};

template <typename T>
T do_nth_power(T x, T acc, unsigned n) // Add an initial value, as is customary in the standard library.
    requires multiplacative<T> && std::copyable<T> // Write dependencies on concepts
{
    // Remove validity checks and leave them to the user.
    while (n > 0)
    {
        if ((n & 0x1) == 0x1) // If odd
        {
            acc *= x;
            n -= 1;
        }
        x *= x;
        n /= 2;
    }
    return acc;
}

unsigned nth_power(unsigned x, unsigned n)
{
    if (x < 2u || n == 1u)
        return x;
    return do_nth_power<unsigned>(x, 1u, n);
}

struct Matrix2x2
{
    int n[2][2];
    bool operator==(const Matrix2x2& m) const
    {
        for (int i = 0; i < 2; ++i)
            for (int j = 0; j < 2; ++j)
                if (n[i][j] != m.n[i][j])
                    return false;
        return true;
    }
    Matrix2x2& operator*=(const Matrix2x2& m)
    {
        Matrix2x2 r;
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                int acc = 0;
                for (int k = 0; k < 2; k++)
                    acc += n[i][k] * m.n[k][j];
                r.n[i][j] = acc;
            }
        }
        *this = r;
        return *this;
    }
};

Matrix2x2 nth_power(Matrix2x2 x, unsigned n)
{
    Matrix2x2 eye{1, 0, 0, 1};
    if (x == eye || n == 1u)
        return x;
    return do_nth_power<Matrix2x2>(x, eye, n);
}

#if ENABLE_FAILS

struct Wrong
{};

Wrong nth_power(Wrong x, unsigned n)
{
    Wrong eye;
    if (n == 1u)
        return x;
    return do_nth_power<Wrong>(x, eye, n);
}

#endif

TEST(nthpower_test_case, testWillPass)
{
    EXPECT_EQ(nth_power(2, 11), (1 << 11));
    EXPECT_EQ(nth_power(2.0, 11), (1 << 11));
    Matrix2x2 m{1, 0, 0, 1};
    EXPECT_EQ(nth_power(m, 5), m);
}