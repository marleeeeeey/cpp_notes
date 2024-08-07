#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

// clang-format off

int main() {
  std::ostream_iterator<int> os(std::cout, " ");
  std::vector<int> a = {8, 4, 2, 1};
  std::vector<int> b = {1, 2, 4, 8,};
  std::vector<int> c;

  // or we can use std::multiplies
  auto transform_op = [](auto &&tx, auto &&ty) { return tx * ty; };
  std::transform(a.begin(), a.end(), b.begin(), std::back_inserter(c), transform_op);
  std::copy(c.begin(), c.end(), os); std::cout << std::endl;

  // or we can use std::plus
  auto reduce_op = [](auto &&rx, auto &&ry) { return rx + ry; };
  auto x = std::transform_reduce(a.begin(), a.end(), b.begin(), 0, reduce_op, transform_op);
  std::cout << "Reduced to: " << x << std::endl;

  auto y = std::inner_product(a.begin(), a.end(), b.begin(), 0);
  std::cout << "Inner product is: " << y << std::endl;
}

// clang-format off