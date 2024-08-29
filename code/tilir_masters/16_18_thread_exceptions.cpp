#include <future>
#include <iostream>
#include <string>
#include <thread>
#include <utility>

#include "gtest/gtest.h"

// clang-format off

TEST(threads, basic)
{
    std::promise<int> p;
    std::future<int> f = p.get_future();

    auto divi = [](auto&& result, auto a, auto b)
    {
        try
        {
            if (b == 0)
                throw std::overflow_error("Divide by zero");    // <--- throw exception
            result.set_value(a / b);
        }
        catch (...)
        {
            result.set_exception(std::current_exception());     // <--- set exception
        }
    };

    std::thread t(divi, std::move(p), 30, 0);
    t.detach();

    try
    {
        auto x = f.get();                                       // <--- get exception
        EXPECT_EQ(0, 1); // we shall not be here
    }
    catch (std::exception& e)                                   // <--- catch exception from future on main thread
    {
        EXPECT_EQ(std::string(e.what()), "Divide by zero");
    }
}