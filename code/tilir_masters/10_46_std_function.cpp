#include "gtest/gtest.h"
#include <functional>
#include <iostream>

// clang-format off

TEST(std_function, basics)
{
    auto closure = [x](int a) { return x - a; };            // <=== Объект на стеке

    std::function<int(int)> factorial = [&](int i)          // <=== Объект в куче (heap indirection)
    {
        return (i == 1) ? 1 : i * factorial(i - 1);
    };

    EXPECT_EQ(factorial(1), 1);
    EXPECT_EQ(factorial(2), 2);

    std::cout << factorial.target_type().name() << std::endl;
}