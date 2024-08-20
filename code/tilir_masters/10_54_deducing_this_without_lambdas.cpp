#include "gtest/gtest.h"
#include <functional>
#include <iostream>

// clang-format off

struct S1
{
    auto foo() const&;
    auto foo() &;
    auto foo() &&;
};

struct S2                       // <=== Начали переписывать под deducing this
{                               //      видим, что можно использовать шаблонный this
    auto foo(this const S&);
    auto foo(this S&);
    auto foo(this S&&);
};

struct S3
{
    template<typename Self>     // <=== Получаем один метод на все случаи
    auto foo(this Self&&);
};


TEST(deducing_this_without_lambdas, basics)
{

}