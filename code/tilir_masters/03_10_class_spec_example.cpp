#include "gtest/gtest.h"

// clang-format off

template <typename T> struct vector {};

template <typename T> struct X {
  int primary = 1;
};

template <typename T> struct X<vector<T>> { // <=== Doen't work for std::vector, because it required 3 parameters.
  int partial = 2;
};

TEST(partialspec, backward) {
  X<int> a;
  X<vector<int>> b;
  EXPECT_EQ(a.primary, 1);
  EXPECT_EQ(b.partial, 2);
}