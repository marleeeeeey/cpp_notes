#include "gtest/gtest.h"
#include <iostream>
#include <string>
#include <variant>

// ЗАДАЧА: надо написать make_overloaded:
// Унаследоваться от каждого из этих классов и получить `operator()`.
// https://youtu.be/j-UyAKux590?t=4448

// clang-format off

template<typename ... F>
struct overloaded : F...
{
    using F::operator()...;
};

template <class... Ts> overloaded(Ts...) -> overloaded<Ts...>;      // <=== deduction hint

TEST(std_custom_overloaded, basics)
{
    auto f = overloaded(
        [](int i) { return "int"; },
        [](double i) { return "double"; },
        [](std::string i) { return "string"; }
    );

    EXPECT_EQ(f(1.5), "double");
    EXPECT_EQ(f(100), "int");

    std::vector<std::variant<int, float, std::string>> vec {1, 2.0f, "3"};
    for (auto& v: vec)
    {
        auto result = std::visit(f, v);
        std::cout << result << std::endl;
    }
}