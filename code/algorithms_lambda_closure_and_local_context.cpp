#include <functional>
#include <iostream>

// clang-format off

auto factory(int parameter)     // 1                2
{
    static int a = 0;           // 0
    return [=]                  // 1                2             // Класс CLOSURE который возращается будет ОДИН ДЛЯ ВСЕХ ОБЪЕКТОВ!
    (int argument)              // 20   30          20      30
    {
        static int b = 0;       // 0    20          50      70
        a += parameter;         // 1    2           4       6
        b += argument;          // 20   50          70      100
        return a + b;           // 21   52          74      106
    };
}

// clang-format on

int main()
{
    auto func1 = factory(1);
    auto func2 = factory(2);
    std::cout << func1(20) << " " << func1(30) << " " << func2(20) << " " << func2(30) << std::endl;
}