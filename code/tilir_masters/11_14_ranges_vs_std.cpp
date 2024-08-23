#include "gtest/gtest.h"
#include <list>
#include <ranges>
#include <vector>

// clang-format off

namespace ranges = std::ranges;
namespace views = std::views;

TEST(rngs, fst)
{
    std::list<int> l = {1, 9, 2, 4, 8, 6, 3, 5, 7}; // <=== Не поддерживает сортировку

#if 1
    ranges::sort(l);                 // <=== Ошибки выглядят лучше (хотя у меня одинаково)
#else
    std::sort(l.begin(), l.end());   // <=== Чем тут : error: no member named 'sort' in namespace 'std'
#endif

    EXPECT_EQ(*l.begin(), 1);
    EXPECT_EQ(*std::next(l.begin()), 2);
}