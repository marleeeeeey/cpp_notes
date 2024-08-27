#include <iostream>
#include <mutex>
#include <thread>

#include "gtest/gtest.h"

// clang-format off

namespace
{

std::mutex osm;
std::ostringstream os;

struct resource
{
    resource()
    {
        {
            std::lock_guard lk{osm};
            os << "c";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    void use()
    {
        {
            std::lock_guard lk{osm};
            os << "u";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
};

resource* resptr;
std::mutex resmut;

void foo()
{
    if (!resptr)                                // <=== Мы читаем значение.
    {
        std::lock_guard<std::mutex> lk{resmut};
        {
            if (!resptr)
                resptr = new resource();        // <=== В момент, когда пишем новое - это UB.
        }
    }
    resptr->use();
}

} // namespace

TEST(threads, affty)
{
    std::thread t1{foo};
    std::thread t2{foo};
    std::thread t3{foo};
    std::thread t4{foo};

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    EXPECT_EQ(os.str(), "cuuuu");
}
