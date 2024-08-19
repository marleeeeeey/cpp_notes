#include "gtest/gtest.h"

// clang-format off
#define ENABLE_FAILS 0

int sum_all()
{
    return 0;
}

#if ENABLE_FAILS == 1

template <typename T, typename... Ts>
T sum_all(T&& arg, Ts&&... args)
{
    return arg +
        sum_all(args...);   // error: non-const lvalue reference to type 'int' cannot bind to a temporary of type 'int'
                            // T = const int&,      Ts = const int&,    return = const int&
}

#endif

template <typename T, typename... Ts>
auto                                    // <=== fix: auto режет тип и выводит return = int - OK
sum_all(T&& arg, Ts&&... args)
{
    return arg + sum_all(args...);
}

template <typename T, typename... Ts>
T
sum_all2(T&& arg, Ts&&... args)
{
    return arg + sum_all(
        std::forward<Ts>(args)...);     // T = int&&,      Ts = int&&,    return = int&& - OK
}

TEST(variadic, cstyle)
{
    int res = sum_all(1, 2, 3, 4);
    int res2 = sum_all2(1, 2, 3, 4);
    EXPECT_EQ(res, 10);
    EXPECT_EQ(res2, 10);
}