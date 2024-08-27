#include <iostream>
#include <mutex>
#include <thread>

#include "gtest/gtest.h"

#define THROW_EXCEPTION 0

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
std::once_flag resflag;

void init_resource()
{
#if THROW_EXCEPTION
    throw std::runtime_error("Exception in init_resource");
#endif
    resptr = new resource();
}

void foo()
{
#if THROW_EXCEPTION
    try
    {
        std::call_once(resflag, init_resource);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
#else
    std::call_once(resflag, init_resource);
#endif
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
