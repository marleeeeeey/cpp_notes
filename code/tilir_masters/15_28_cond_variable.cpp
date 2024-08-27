#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

#include "gtest/gtest.h"

#define ENABLE_FAIL 1
#define ENABLE_FOCUS_TO_FIX_FAIL 0

namespace
{

std::mutex gmut;
int counter = 0;
std::condition_variable data_cond;

void processing()
{
    int c;
#if ENABLE_FOCUS_TO_FIX_FAIL
    std::cout << "w";
#endif
    {
        std::unique_lock<std::mutex> lk{gmut};
        data_cond.wait(lk, [] { return counter > 0; });
        // here lock for gmut obtained
        c = counter;
    }
    std::cout << "-";
}

void preparation()
{
    {
        std::lock_guard<std::mutex> lk{gmut};
        // here lock for gmut obtained
        counter += 1;
        data_cond.notify_one();
    }
    std::cout << "+";
}

} // namespace

TEST(threads, affty)
{
#if ENABLE_FAIL
    std::thread t3{processing};
#endif
    std::thread t2{processing};
    std::thread t1{preparation};
    t1.join();
    t2.join();
    t3.join();
    std::cout << "\n";
    EXPECT_EQ(counter, 1);
}
