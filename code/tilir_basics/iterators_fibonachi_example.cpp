#include <iostream>
#include <utility>

// RANGE BASE LOOP FOR STD::VECTOR use (https://cppinsights.io):
//   range.begin()
//   range.end()
//   operator!=(it1, it2)
//   operator++()
//   operator*()
// -----------------------------------------------------------------------
// std::vector<int, std::allocator<int> > & __range1 = arr;
// auto __begin1 = __range1.begin();
// auto __end1 = __range1.end();
// for(; __gnu_cxx::operator!=(__begin1, __end1); __begin1.operator++()) {
//   const char & c = static_cast<const char>(__begin1.operator*());
// }

// clang-format off

struct fibit
{
    int prev = 0;
    int cur = 1;

    fibit& operator++()
    {
        prev = std::exchange(cur, prev+cur);
        return *this;
    }

    int operator*() { return cur; }
    auto operator<=>(const fibit&) const = default;
};

struct fibonachi {};
fibit begin(fibonachi) { return{}; }
fibit end(fibonachi) { return{144, 233}; }

// clang-format on

int main()
{
    for (auto&& value : fibonachi{})
        std::cout << value << " ";

    std::cout << std::endl;
}