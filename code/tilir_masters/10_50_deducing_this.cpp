#include "gtest/gtest.h"
#include <functional>
#include <iostream>

// clang-format off

TEST(deducing_this, basics)
{
    // BEFORE
    std::function<int(int)> factorial1 =                // <=== делаем type erasure
                                            [&]         // <=== необходимо было делать захват
                                            (int i)
    {
        return (i == 1) ? 1 : i * factorial1(i - 1);
    };
    EXPECT_EQ(factorial1(5), 120);

    // BEFORE from HolyBlackCat
    // Лучше std::function, потому что не изпользуется куча
    // и скорее всего компилятор сможет это соптимизировать
    auto factorial2 = [](auto &factorial2, int i) -> int
    {
        return i == 1 ? 1 : i * factorial2(factorial2, i - 1);
    };
    EXPECT_EQ(factorial2(factorial2, 5), 120);

    // НОВЫЙ СПОСОБ - без стирания типа
    auto factorial_new = [] (this auto && self, int i) -> int
    {
        return (i == 1) ? 1 : i * self(i - 1);
    };
    EXPECT_EQ(factorial_new(5), 120);
}