#include "gtest/gtest.h"
#include <concepts>
#include <type_traits>

/*
Practice with concepts and variadic templates.
- Calculate the sum of all integers in a variadic template. All other types are ignored (converted to 0).
*/

template <typename T>
concept Numeric = std::integral<T> || std::floating_point<T>;

// Primary template - always return 0
auto get_numberic_value(auto value)
{
    return 0;
}

// Specialization for Numeric
auto get_numberic_value(Numeric auto value)
{
    return value;
}

template <typename... Ts>
auto sum_all_int(Ts... ts)
{
    if constexpr (sizeof...(Ts) == 0) // <=== Support empty parameter list: sum_all_int()
        return 0;
    else
        return (get_numberic_value(ts) + ...);
}

TEST(variadic_templates_with_concepts, sum_all_int)
{
    EXPECT_EQ(sum_all_int(1, 2, 4, 1.5, "erqwerq"), 8.5);
    EXPECT_EQ(sum_all_int(1), 1);
    EXPECT_EQ(sum_all_int(1, 1), 2);
    EXPECT_EQ(sum_all_int(), 0);
    EXPECT_EQ(sum_all_int("qwer"), 0);
}

TEST(variadic_templates_with_concepts, check_return_types)
{
    EXPECT_EQ(std::is_integral<decltype(sum_all_int(1))>::value, true);
    EXPECT_EQ(std::is_integral<decltype(sum_all_int(1.5))>::value, false);
}
