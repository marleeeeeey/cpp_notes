#include "gtest/gtest.h"
#include <iostream>

// Написать класс для конкатенации битовых масок.
// Сделать это в compile-time, чтобы такое можно было использовать в switch.
enum class bitmask
{
    b0 = 0x1,
    b1 = 0x2,
    b2 = 0x4
};

consteval bitmask operator|(bitmask v0, bitmask v1)
{
    return static_cast<bitmask>(int(v0) | int(v1));
}

TEST(ct_trit, basic)
{
    EXPECT_EQ(static_cast<int>(bitmask::b0 | bitmask::b1), 3);

    bitmask b = static_cast<bitmask>(3); // 0b11

    switch (b)
    {
    case bitmask::b0 | bitmask::b1:
        std::cout << "switch done" << std::endl;
        break;
    }
}