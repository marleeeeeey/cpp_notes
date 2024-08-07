#define ENABLE_FAILS 0

// clang-format off

template <typename T> constexpr int somepred() { return 14; }

template <typename T> requires (somepred<T>() == 42) // Делает вычисления в compile-time: (14 == 42) = false
bool foo (T&& lhs, T&& rhs) { return lhs < rhs; }

template <typename T>
requires requires (T t) { somepred<T>() == 42; } // НЕ делает вычисления, а только оценивает применимость ==.
bool bar (T&& lhs, T&& rhs) { return lhs < rhs; }

int
main () {
#if ENABLE_FAILS
  foo(1, 2);
#else
  bar(1, 2);
#endif
}