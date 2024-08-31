//-----------------------------------------------------------------------------
//
// Source code for MIPT masters course on C++
// Slides: https://sourceforge.net/projects/cpp-lects-rus
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// Parallel algorithm test
//
//----------------------------------------------------------------------------

#include <coroutine>

#include "gtest/gtest.h"

// clang-format off

namespace {

template <typename T> struct generator {
  struct promise_type {
    T current_value;                                                        // (1). Добавили поле для хранения значения (состояния)
    using coro_handle = std::coroutine_handle<promise_type>;
    auto get_return_object() { return coro_handle::from_promise(*this); }
    auto initial_suspend() { return std::suspend_always(); }
    auto final_suspend() noexcept { return std::suspend_always(); }
    void return_void() {}
    void unhandled_exception() { std::terminate(); }
    auto yield_value(T value) {                                             // (2). Для поддержки co_yield добавили метод yield_value
      current_value = value;
      return std::suspend_always{};
    }
  };

  using coro_handle = std::coroutine_handle<promise_type>;
  bool move_next() {
    return handle_ ? (handle_.resume(), !handle_.done()) : false;
  }
  T current_value() const { return handle_.promise().current_value; }       // (3). Добавили метод для получения значения (состояния)
  generator(coro_handle h) : handle_(h) {}
  generator(generator const &) = delete;
  generator(generator &&rhs) : handle_(rhs.handle_) { rhs.handle_ = nullptr; }
  ~generator() {
    if (handle_)
      handle_.destroy();
  }

private:
  coro_handle handle_;
};

}

namespace {

generator<int> natural_nums() {
  int num = 0;                      // Эта переменная копируется в состояние генератора
  for (;;) {
    co_yield num;
    num += 1;
  }
}

}

TEST(parallel, reduce) {
  int n = 0;
  auto nums = natural_nums();

  for (int i = 0; i < 10; ++i) {
    nums.move_next();
    auto y = nums.current_value();
    EXPECT_EQ(y, n);
    auto z = nums.current_value();
    EXPECT_EQ(z, n);
    n = n + 1;
  }
}
