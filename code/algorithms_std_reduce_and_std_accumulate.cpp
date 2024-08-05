#include <algorithm>
#include <execution>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

// clang-format off

int main() {
    std::ostream_iterator<int> os(std::cout, " ");
    std::vector<int> a = {8, 4, 2, 1};
    std::copy(a.begin(), a.end(), os); std::cout << std::endl;

    auto mults = std::reduce(
      std::execution::par,                            // execution policy. Random order
      a.begin(), a.end(),
      1,                                              // init
      [](auto&& v1, auto&& v2) { return v1*v2; });    // binary op
    std::cout << mults << std::endl;

    auto plus_result = std::reduce(a.begin(), a.end());    // std::plus by default
    std::cout << plus_result << std::endl;


    auto multsAcc = std::accumulate(
                                                        // No exec policy. Works in order
      a.begin(), a.end(),
      1,                                                // init
      [](auto&& v1, auto&& v2) { return v1*v2; });      // binary op
    std::cout << multsAcc << std::endl;
}

// clang-format off