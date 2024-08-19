#include "gtest/gtest.h"
#include <tuple>
#include <utility>

// clang-format off

TEST(lamdas, perfect_forward)
{
    auto foo = []<typename ... T>(T&&... a)
    {
        return
            [a = std::forward_as_tuple(a...)]       // <=== Форвардим каждый элемент в пачке
            () mutable
        {
            return ++std::get<0>(a);
        };
    };

    auto f1 = foo(1);       // expect rvalue
    EXPECT_EQ(f1(), 2);

    int x = 1;
    auto f2 = foo(x);       // expect lvalue
    EXPECT_EQ(f2(), 2);

    EXPECT_EQ(x, 2);        // OK: x = 2
}