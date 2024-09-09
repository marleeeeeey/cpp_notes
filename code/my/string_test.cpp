#include "gtest/gtest.h"
#include <algorithm>
#include <string>

TEST(string, find)
{
    std::string msg;
    EXPECT_EQ(msg.find('\n') == std::string::npos, true);
    EXPECT_EQ(msg.find('\n'), false); // <===
}