#include <cassert>
#include <cstddef>
#include <iostream>
#include <type_traits>

// clang-format off

template <size_t N> struct fibonacci
    : std::integral_constant<size_t, fibonacci<N-1>{} + fibonacci<N-2>{}> {};

template<> struct fibonacci<0> : std::integral_constant<size_t, 0>{};
template<> struct fibonacci<1> : std::integral_constant<size_t, 1>{};

// clang-format on

int main()
{
    // Task: write compile time computations of fibonacci via SFINAE

    //                              9
    //                              v
    // 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233

    std::cout << "fibonacci<9> " << fibonacci<9>() << std::endl;
    assert(fibonacci<9>() == 34);
}