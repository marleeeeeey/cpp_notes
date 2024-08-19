#include "gtest/gtest.h"
#include <tuple>

// clang-format off

TEST(std_apply, basics)
{
    auto add = [](auto x, auto y) { return x + y; };
    auto sum1 = std::apply(add, std::pair(1, 2));
    EXPECT_EQ(sum1, 3);

    auto mult = std::apply( [](auto&&... xs)
                                { return (1 * ... * xs); },
                            std::make_tuple(1, 2, 3, 4, 5));
    EXPECT_EQ(mult, 120);

    // for_each для каждого элемента tuple
    // форвардинг добавить самостоятельно и починить ошибки компиляции TODO
    // auto fn = add;
    // auto t = std::make_tuple(1, 2, 3.0, 4);
    // auto sum2 = std::apply([&fn](auto&& ... xs) {(fn(xs), ...);}, t);
    // EXPECT_EQ(sum2, 10.0);
}