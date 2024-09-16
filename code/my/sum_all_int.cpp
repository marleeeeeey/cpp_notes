#include <concepts>
#include <iostream>

template <typename T>
concept Numeric = std::integral<T> || std::floating_point<T>;

double get_numberic_value(auto value)
{
    return 0;
}

double get_numberic_value(Numeric auto value)
{
    return value;
}

template <typename... Ts>
int sum_all_int(Ts... ts)
{
    return (get_numberic_value(ts) + ...);
}

int main()
{
    auto result = sum_all_int(1, 2, 4, 1.5, "erqwerq");
    std::cout << result << "\n";
}
