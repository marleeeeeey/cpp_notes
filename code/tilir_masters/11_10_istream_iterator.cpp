#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

// clang-format off

int main()
{
    auto& os = std::cout;
    auto& is = std::cin;

    std::for_each(
        std::istream_iterator<int>{is},
        std::istream_iterator<int>{},                           // <=== Сингулярный итератор
        [&os](int d) { if (d < 5) { os << d * 2 << " "; } });
}