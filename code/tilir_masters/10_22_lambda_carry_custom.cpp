#include <cassert>
#include <functional>

// clang-format off
// ЗАДАЧА: Написать функцию curry, которая частично применяет аргументы к функции

auto add = [](auto x, auto y)
{
    return x + y;
};

template <typename Fun, typename... Args>
auto curry(Fun fun, Args... args)                   // <=== Съедаем первую часть аргументов
{
    return [=](auto... rest)                        // <=== Съедаем все остальные аргументы
    {
        return std::invoke(fun, args..., rest...);  // <=== Восстанавливаем вызов со всеми аргументами
    };
}

int main()
{
    auto add4 = curry(add, 4);
    assert(add4(11) == 15);
}
