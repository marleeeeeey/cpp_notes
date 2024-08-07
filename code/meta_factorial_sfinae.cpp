#include <cassert>
#include <cstddef>
#include <iostream>
#include <type_traits>

// clang-format off

template <size_t N> struct factorial
    : std::integral_constant<size_t, N * factorial<N-1>{}> {};

template<> struct factorial<0>
    : std::integral_constant<size_t, 1>{};

// clang-format on

int main()
{
    // Task: write compile time computations of factorial via SFINAE

    // 5! = 1 * 2 * 3 * 4 * 5 = 120
    std::cout << "factorial<5> " << factorial<5>() << std::endl;
    assert(factorial<5>() == 120);
}