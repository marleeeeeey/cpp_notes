#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <vector>

// clang-format off

int main() {
  std::ostream_iterator<int> os(std::cout, " ");
  std::vector<int> v; // пустой вектор
  auto id = [] (auto &&x) { return x; };
  if (std::all_of(v.begin(), v.end(), id))  // std::all_of TRUE для пустого диапазона
    std::cout << "All\n";
  if (std::any_of(v.begin(), v.end(), id))  // std::all_of FALSE для пустого диапазона
    std::cout << "Any\n";
  if (std::none_of(v.begin(), v.end(), id)) // std::all_of TRUE для пустого диапазона
    std::cout << "None\n";
}

// clang-format on