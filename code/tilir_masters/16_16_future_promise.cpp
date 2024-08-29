#include <future>
#include <iostream>
#include <thread>
#include <utility>

#include "gtest/gtest.h"

TEST(threads, basic)
{
    std::promise<int> p;
    std::future<int> f = p.get_future();

    auto divi = [](auto&& result, auto a, auto b)
    {
        result.set_value(a / b);
    };

    std::thread t(divi, std::move(p), 30, 6);
    t.detach();

    EXPECT_EQ(f.get(), 5);
}
