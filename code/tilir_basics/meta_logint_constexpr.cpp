#include <climits>
#include <cstddef>
#include <iostream>

#define USE_CONSTEXPR 0
#define USE_CONSTEVAL 1

// clanf-format off

// Определить позицию единичного бита в числе
#if USE_CONSTEVAL
consteval
#elif USE_CONSTEXPR
constexpr
#endif
    size_t
    log_int(size_t N)
{
    size_t pos = sizeof(size_t) * CHAR_BIT; // Изначально равно количеству бит.
    size_t mask = 0;

    if (N == 0)
        throw "N == 0 not supported";

    do
    {
        pos -= 1; // Начинаем со старшего бита
        mask = 1ull << pos;
    }
    while ((N & mask) != mask); // ???

    if (N != mask)
        pos += 1;

    return pos;
}

// clanf-format on

int main()
{
#if USE_CONSTEVAL
    std::cout << "log_int(8) = " << log_int(8) << std::endl;
#else
    for (auto i : {1, 2, 3, 4, 5, 6, 7, 8, 9})
    {
        std::cout << "log_int(" << i << ") = " << log_int(i) << std::endl;
    }
#endif
}