#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

// clang-format off

int main()
{
    // _FwdIt rotate(_FwdIt _First, _FwdIt _Mid, _FwdIt _Last)

    std::ostream_iterator<int> osit{std::cout, " "};
    std::vector<int> v(10);
    std::iota(v.begin(), v.end(), 1);               // 1  2  3  4  5  6  7  8  9  10
    std::copy(v.begin(), v.end(), osit);
    std::cout << std::endl;

    auto first = std::find(v.begin(), v.end(), 3);  //       ^
    auto last = std::find(v.begin(), v.end(), 6);   //                ^
    auto pos = std::find(v.begin(), v.end(), 8);    //                      ^
    std::rotate(first, last, pos);                  // 1  2  6  7  3  4  5  8  9  10
    std::copy(v.begin(), v.end(), osit);
    std::cout << std::endl;

    std::iota(v.begin(), v.end(), 1);               // 1  2  3  4  5  6  7  8  9  10
    pos = std::find(v.begin(), v.end(), 2);         //    ^
    first = std::find(v.begin(), v.end(), 7);       //                   ^
    last = std::find(v.begin(), v.end(), 9);        //                         ^
    std::rotate(pos, first, last);                  // 1  7  8  2  3  4  5  6  9  10
    std::copy(v.begin(), v.end(), osit);
    std::cout << std::endl;
}

// clang-format on