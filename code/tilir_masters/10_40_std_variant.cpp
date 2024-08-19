#include "gtest/gtest.h"
#include <string>
#include <variant>
#include <vector>

TEST(std_variant, basics)
{
    std::variant<int, float> v = 12;
    EXPECT_EQ(std::get<int>(v), 12);
    EXPECT_EQ(std::holds_alternative<float>(v), false);

    std::vector<std::variant<int, float, std::string>> vec = {10, 1.5f, "hello"};

    for (auto& v : vec)
    {
        std::visit(
            [](auto&& arg)
            {
                using T = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<T, int>) // <=== Используем if constexpr, чтобы делать специфичные для
                                                      //      типов операции.
                {
                    std::cout << arg % 5 << std::endl;
                }
                else if constexpr (std::is_same_v<T, float>)
                {
                    std::cout << "I am a float " << std::round(arg) << std::endl;
                }
            },
            v);
    }
}