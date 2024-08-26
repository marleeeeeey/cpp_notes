#include <iostream>
#include <thread>

// clang-format off

#include "gtest/gtest.h"

TEST(threads, basic)
{
    int j = 0;
    std::thread t([&j] { j += 1; });
    t.join();                           // <=== Ожидание завершения потока
    EXPECT_EQ(j, 1);
}

TEST(threads, basic2)                   // <=== Тут вывод может перемешаться, но это не гонка.
{
  std::thread t([]() {
    std::cout << "Spawned id: " << std::this_thread::get_id() << std::endl;
  });
  std::cout << "Parent id: " << std::this_thread::get_id() << std::endl;
  t.join();
}

