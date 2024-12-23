#include "gtest/gtest.h"

template <typename T>
struct default_id_trait
{
    static int id() { return 1; }
};

template <typename T, typename Trait = default_id_trait<T>>
T nth_power(T x, unsigned n)
{
    T acc = Trait::id(); // <----------------------------------
    if ((x == acc) || (n == 1))
        return x;
    while (n > 0)
    {
        if ((n & 0x1) == 0x1)
        {
            acc *= x;
            n -= 1;
        }
        x *= x;
        n /= 2;
    }
    return acc;
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

template <>
struct default_id_trait<Matrix2x2> // <----------------------------------
{
    static Matrix2x2 id() { return {1, 0, 0, 1}; }
};

TEST(nthpower_test_case, testWillPass)
{
    EXPECT_EQ(nth_power(2, 11), (1 << 11));
    EXPECT_EQ(nth_power(2.0, 11), (1 << 11));
    Matrix2x2 m{1, 0, 0, 1};
    EXPECT_EQ(nth_power(m, 5), m);
}