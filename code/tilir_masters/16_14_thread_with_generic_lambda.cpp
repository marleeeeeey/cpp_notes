#include <iostream>
#include <thread>

#include "gtest/gtest.h"

TEST(threads, basic)
{
    int result = 42;

    auto divi = [](auto&& result, auto a, auto b)
    {
        result.get() = a / b;
    };

    std::thread t(divi, std::ref(result), 30, 6);
    t.join();
    EXPECT_EQ(result, 5);
}