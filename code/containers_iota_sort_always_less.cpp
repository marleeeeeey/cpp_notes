#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

int main()
{
    std::vector<int> v(120);
    std::ostream_iterator<int> osit(std::cout, " ");
    std::iota(v.begin(), v.end(), 0);
    std::sort(
        v.begin(), v.end(),
        [](auto lhs, auto rhs) { return false; }); // Всегда возвращает false, значит все значения равны!!!
    std::copy(v.begin(), v.end(), osit);
}
