#include <future>
#include <iostream>
#include <thread>
#include <utility>

#include "gtest/gtest.h"

#define THROW_EXCEPTION 1

TEST(threads, basic)
{
    auto divi = [](auto a, auto b)
    {
        if (b == 0)
            throw std::overflow_error("Divide by zero");
        return a / b;
    };

    std::packaged_task<int(int, int)> task{divi};
    std::future<int> f = task.get_future();
#if THROW_EXCEPTION
    std::thread t(std::move(task), 30, 0);
#else
    std::thread t(std::move(task), 30, 5);
#endif
    t.detach();

    try
    {
        auto x = f.get();
        EXPECT_EQ(x, 6);
    }
    catch (std::exception& e)
    {
        EXPECT_STREQ(e.what(), "Divide by zero");
    }
}