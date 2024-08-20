#include "gtest/gtest.h"

// ЗАДАЧА: надо написать make_overload:
// Унаследоваться от каждого из этих классов и получить `operator()`.
// https://youtu.be/j-UyAKux590?t=4448

// clang-format off

template<typename ... F>
struct overload : F...                                  // <=== 2. Наследуемся от Лямбд
{
    using F::operator()...;                             // <=== 3. (C++17) using F::operator()...;
    overload(F... f) : F(f)... {}
};

template<typename ... F>
auto make_overload(F ... f)
{
    return overload<F...>(f...);
}

TEST(std_custom_overload, basics)
{
    auto f = make_overload(
        [](int i) { std::cout << "int\n"; },            // <=== 1. Создаем класс лямбды
        [](double i) { std::cout << "double\n"; }
    );

    f(1.5);
    f(100);
}