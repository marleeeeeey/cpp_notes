#include <iostream>
#include <utility>

#define USE_REQUIERES_CONSTRAINS 1

// clang-format off

#if USE_REQUIERES_CONSTRAINS

// constraints: ok

template <typename T> requires (sizeof(T) > 4)
void foo (T x) { std::cout << "For large" << std::endl; }

template <typename T> requires (sizeof(T) <= 4)
void foo (T x) { std::cout << "For small" << std::endl; }

#else

// SFINAE: not working

template <typename T, typename = std::enable_if_t<(sizeof(T) > 4)>>
void foo (T x) { std::cout << "For large" << std::endl; }

template <typename T, typename = std::enable_if_t<(sizeof(T) <= 4)>>
void foo (T x) { std::cout << "For small" << std::endl; }

#endif

// clang-format on

int main()
{
    foo('a');
    foo(1LL);
}
