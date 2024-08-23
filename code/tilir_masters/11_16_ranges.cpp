#include "gtest/gtest.h"
#include <algorithm>
#include <cmath>
#include <list>
#include <ranges>
#include <sstream>
#include <type_traits>
#include <vector>

// clang-format off

namespace ranges = std::ranges;
namespace views = std::views;

struct A { int x, y; };

bool operator==(const A &a, const A &b) { return a.x == b.x && a.y == b.y; }
std::tuple<int, int> tp(const A &a) { return {a.x, a.y}; }

TEST(rngs, fst)
{
    std::vector<A> vec = {{1, 2}, {7, 8}, {3, 4}, {5, 6}, {9, 10}};

    auto test = [&vec]
    {
        auto left = std::tuple(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
        auto right = std::tuple_cat(tp(vec[0]), tp(vec[1]), tp(vec[2]), tp(vec[3]), tp(vec[4]));
        EXPECT_EQ(left, right);
    };

    ranges::sort(vec, [](const A &a, const A &b) { return a.x < b.x; });    // <=== use comparator
    test();

    ranges::sort(vec, {}, [](auto &&a) { return a.x; } );                   // <=== use projection
    test();

    ranges::sort(vec, {}, &A::x);                                           // <=== use projection (shorter)
    test();
}