#include <iostream>

#define USE_CONSTEXPR 1

// clang-format off

template <typename Head, typename... Args>
void print_all(Head&& head, Args&&... args)
{
    std::cout << head;
    if
#if USE_CONSTEXPR
    constexpr
#endif
    (sizeof...(args) > 0)               // This branch will be removed at the second phase of template instantiation
    {
        std::cout << "_";
        print_all(args...);             // That is why here will not be an error.
    }
}

// clang-format on

int main()
{
    print_all("hello", 123, 5.24);
}