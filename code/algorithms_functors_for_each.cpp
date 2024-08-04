#include <algorithm>
#include <execution>
#include <map>

void f(std::pair<int, int> p)
{
    // do something with p
}

// clang-format off

int main()
{
    std::map<int, int> m = {{1, 2}, {3, 4}, {5, 6}};
    auto [begin, end] = m.equal_range(3);

    for (auto it = begin; it != end; ++it)  f(*it);     // 1
    std::for_each(begin, end, f);                       // 2

    std::for_each(std::execution::par, begin, end, f);  // 2.1
}

// clang-format on