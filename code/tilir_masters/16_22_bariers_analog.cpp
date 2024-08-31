#include <future>
#include <iostream>
#include <thread>
#include <utility>


#include "gtest/gtest.h"

namespace chrono = std::chrono;

constexpr int NSLEEP = 1;

int G = 1;

void prepare(std::promise<void>&& Ready, std::shared_future<void> BackLink)
{
    std::this_thread::sleep_for(chrono::milliseconds(NSLEEP));
    EXPECT_EQ(G, 1);
    Ready.set_value();
    BackLink.wait(); // --- hold here ---
    EXPECT_EQ(G, 2);
}

TEST(threads, basic)
{
    std::promise<void> Proceed;
    std::shared_future<void> ProceedF = Proceed.get_future();

    std::promise<void> FirstReady;
    std::future<void> FirstReadyF = FirstReady.get_future();
    std::thread Fst(prepare, std::move(FirstReady), ProceedF);

    std::promise<void> SecondReady;
    std::future<void> SecondReadyF = SecondReady.get_future();
    std::thread Snd(prepare, std::move(SecondReady), ProceedF);

    // wait everybody ready
    FirstReadyF.wait();
    SecondReadyF.wait();

    G = 2;

    Proceed.set_value(); // resume work with promise

    Fst.join();
    Snd.join();
}