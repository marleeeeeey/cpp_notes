#include "gtest/gtest.h"
#include <string>

/*
Faced with a problem when trying find a character in a string and use it in a condition.
- find() method returns std::string::npos when the character is not found.
- Returns the position of the character in the string when it is found.
- Returning value 0 means the character is found at the beginning of the string. <===
  - Checking `if (msg.find('\n'))` is not correct!!!
*/

TEST(string, find)
{
    std::string msg;
    EXPECT_EQ(msg.find('\n') == std::string::npos, true);
    EXPECT_EQ(msg.find('\n'), false); // <===
}