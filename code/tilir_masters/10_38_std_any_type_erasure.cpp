#include "gtest/gtest.h"
#include <any>

struct HeavyObject
{
    int value;
};

TEST(std_any, basics)
{
    std::any a = 1;
    EXPECT_EQ(std::any_cast<int>(a), 1);
    EXPECT_EQ(a.has_value(), true);
    a.reset();
    EXPECT_EQ(a.has_value(), false);
    auto h = std::make_any<HeavyObject>(100);
}