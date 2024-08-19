#include "gtest/gtest.h"
#include <iostream>
#include <vector>

template <typename Range, typename Callable>
void print_range(Range&& r, Callable&& c)
{
    for (auto&& e : std::forward<Range>(r))
        std::cout << std::invoke(std::forward<Callable>(c), std::forward<decltype(e)>(e)) << " ";
    std::cout << std::endl;
}

TEST(lamdas, renaming_move_fail)
{
    std::vector<std::pair<int, int>> v = {{1, 1}, {2, 2}, {3, 3}};
    print_range(v, [](const auto& p) { return p.second; });
    print_range(v, &std::pair<int, int>::second);
}