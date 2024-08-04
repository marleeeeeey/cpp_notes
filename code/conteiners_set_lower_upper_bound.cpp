#include <iostream>
#include <set>

#define USE_GREATER_INSTEAD_OF_LESS 0

// Концепция равных элементов теряется, т.к. a <= b и b <= a, не означает, что a == b.
// При заполнении множества возникнут проблемы, потому что каждый элемент будет считаться уникальным.
// Т.е. равные элементы считаются неравными.
#define USE_LESS_EQUAL_INSTEAD_OF_LESS 0

// clang-format off

int main()
{
    std::set<int
#if USE_GREATER_INSTEAD_OF_LESS
        , std::greater<int>
#elif USE_LESS_EQUAL_INSTEAD_OF_LESS
        , std::less_equal<int>
#endif
        > s = {67, 42, 141, 23, 42, 106, 15, 50};
    auto itb = s.lower_bound(30); // Return iterator to the first element NOT LESS than the given value. `[`
    auto ite = s.upper_bound(100); // Return iterator to the first element GREATER than the given value. `)`
    for (auto it = itb; it != ite; ++it)
        std::cout << *it << std::endl;
}

// clang-format on