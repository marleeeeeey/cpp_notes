#include <iostream>
#include <thread>

#include "gtest/gtest.h"

// clang-format off

unsigned x = 0,         // <=== x - является скалярным объектом, поэтому ниже data race
    i = 0, j = 0;
char x2[] = {0, 0};     // <=== x2 - не является скалярным объектом, поэтому гонки нет

// std::cout            // <=== std::cout - не является скалярным объектом. Это структура.
                        //      Т.е. это точно не область памяти. А будет гонка или UB, зависит
                        //      от реализации std::cout - есть ли внутрии нее скалярные не атомарные объекты.

void __attribute__((noinline)) use(int c)
{
    asm("");
}

void readerf()
{
    while (i++ < 'g')
    {
        x += 0x1;
        x2[0] += 0x1;
        use(x);
    }
}

void writerf()
{
    while (j++ < 'g')
    {
        x += 0x10000;
        x2[1] += 0x1;
        use(x);
    }
}

TEST(threads, locations)
{
    std::thread t1{readerf}, t2{writerf};
    t1.join();
    t2.join();
    EXPECT_EQ(x & 0xFF, 'g');
    EXPECT_EQ((x >> 16) & 0xFF, 'g');
    EXPECT_EQ(x2[0], 'g');
    EXPECT_EQ(x2[1], 'g');
}
