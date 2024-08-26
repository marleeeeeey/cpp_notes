#include <iostream>
#include <thread>
// #include <unistd.h>

#include "gtest/gtest.h"

int foo(int* p)
{
    return *p;
}
int bar(const int* p)
{
    return *p;
}
int buz(volatile int* p)
{
    return *p;
}

TEST(threads, affty)
{
    int i = 1;
    const int ci = 2;
    volatile int vi = 3;
    EXPECT_EQ(foo(&i), 1);
    // foo(&ci);
    // foo(&vi);
    EXPECT_EQ(bar(&i), 1);
    EXPECT_EQ(bar(&ci), 2);
    // bar(&vi);
    EXPECT_EQ(buz(&i), 1);
    // buz(&ci);
    EXPECT_EQ(buz(&vi), 3);
}
