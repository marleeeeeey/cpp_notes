#include "gtest/gtest.h"

// clang-format off

template <typename T> struct FImpl {
  static int f(T t) { return 0; }
};

template <typename T> struct FImpl<T*> {
  static int f(T* t) { return 1; }
};

template <typename T> int f(T t) { return FImpl<T>::f(t); }

TEST(partialspec, backward) {
  int x;
  int *px;
  double y;
  double *py;

  EXPECT_EQ(f(x), 0);
  EXPECT_EQ(f(px), 1);
  EXPECT_EQ(f(y), 0);
  EXPECT_EQ(f(py), 1);
}