#include <iostream>

// clang-format off

auto factory(int parameter)
{
    static int a = 0;           // Этот член будет общим

    return [=](int argument)    // <=== Этот вызов всегда возвращает один и тот же класс
    {
        static int b = 0;       // Этот член будет общим
        a += parameter;
        b += argument;
        return a + b;
    };
}

int main()
{
    auto func1 = factory(1);
    auto func2 = factory(2);
    std::cout << func1(20) << " " << func1(30) << " " << func2(20) << " " << func2(30) << std::endl;
}