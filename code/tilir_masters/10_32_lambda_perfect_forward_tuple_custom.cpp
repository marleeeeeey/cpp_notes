#include "gtest/gtest.h"
#include <utility>

// clang-format off

template <typename ... T>
auto fwd_capture(T&&... x)
{
    return std::tuple<T...>             // <=== std::tuple - cтандартный тип, который может хранить в себе пачку
        (std::forward<T>(x)...);
}

TEST(lamdas, perfect_forward)
{
    auto foo = []<typename T>(T&& a)
    {
        return [a = fwd_capture(a)]() mutable
        {
            return ++std::get<0>(a);    // <=== std::get
        };
    };

    auto f1 = foo(1);       // expect rvalue
    EXPECT_EQ(f1(), 2);

    int x = 1;
    auto f2 = foo(x);       // expect lvalue
    EXPECT_EQ(f2(), 2);

    EXPECT_EQ(x, 2);        // OK: x = 2
}