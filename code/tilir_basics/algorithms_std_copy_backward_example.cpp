#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

// clang-format off

int main()
{
    std::ostream_iterator<int> os(std::cout, " ");
    std::vector<int> a(10);
    std::iota(a.begin(), a.end(), 1);
    std::copy(a.begin(), a.end(), os);
    std::cout << std::endl;
                                                    //  1   2   3   4   5   6   7   8   9   10
    auto first = std::find(a.begin(), a.end(), 1);  //  ^
    auto last = std::next(first, 5);                //                      ^
    auto pos = std::find(a.begin(), a.end(), 4);    //              ^
    auto dpos = std::next(pos, 5);                  //                                  ^
    std::copy_backward(first, last, dpos);          //  [                   )           @
    std::copy(a.begin(), a.end(), os);              //  1   2   3   1   2   3   4   5   9   10
    std::cout << std::endl;
}

// clang-format on