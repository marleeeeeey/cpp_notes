#include "gtest/gtest.h"
#include <vector>

// clang-format off

template <typename ... Args>
int foo(Args ... args) {
  auto lm1 = [args...] { return sizeof...(args); };                 // возможность раскрыть пачку в списке инициализации
  auto lm2 = [...xs = args] { return sizeof...(xs); };              // захват пачки
  auto lm3 = [&...xs = args] { return sizeof...(xs); };             // захват пачки с capture reference
  auto lm4 = [...xs = std::move(args)] { return sizeof...(xs); };   // захват пачки с переименованием
  return lm1() + lm2() + lm3() + lm4();
}

TEST(lamdas, generic) {
  auto result = foo(1, 2.0, std::vector{1, 2, 3});
  EXPECT_EQ(result, 12);
}