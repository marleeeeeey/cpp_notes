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

struct resumable {
  struct promise_type {
    using coro_handle = std::coroutine_handle<promise_type>;
    auto get_return_object() { return coro_handle::from_promise(*this); }
    auto initial_suspend() { return std::suspend_always(); }
    auto final_suspend() noexcept { return std::suspend_always(); }
    void return_void() {}
    void unhandled_exception() { std::terminate(); }
  };

  using coro_handle = std::coroutine_handle<promise_type>;
  resumable(coro_handle handle) : handle_(handle) { assert(handle); }
  resumable(resumable &) = delete;
  resumable(resumable &&rhs) : handle_(rhs.handle_) { rhs.handle_ = nullptr; }
  bool resume() {
    if (!handle_.done())
      handle_.resume();
    return !handle_.done();
  }
  ~resumable() {
    if (handle_)
      handle_.destroy();
  }

private:
  coro_handle handle_;
};

}

namespace {

int G = 0;

resumable foo() {
  G += 1;
  co_await std::suspend_always();
  G += 1;
}

}

TEST(coroutines, resumable) {
  EXPECT_EQ(G, 0);
  auto t = foo();
  EXPECT_EQ(G, 0);              // Вызвался auto initial_suspend() { return std::suspend_always(); } - вернул 0.

  bool ret = t.resume();
  EXPECT_EQ(ret, true);
  EXPECT_EQ(G, 1);

  ret = t.resume();
  EXPECT_EQ(ret, false);        // WHY FALSE?
  EXPECT_EQ(G, 2);

  ret = t.resume();
  EXPECT_EQ(ret, false);
}
