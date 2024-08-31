//-----------------------------------------------------------------------------
//
// Source code for MIPT masters course on C++
// Slides: https://sourceforge.net/projects/cpp-lects-rus
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// Range-based generation
//
//----------------------------------------------------------------------------

#include <coroutine>
#include <future>

#include "gtest/gtest.h"

// clang-format off

namespace {

template <typename T> struct range_gen {
  struct promise_type {
    const T *value = nullptr;
#ifdef BUG
    auto get_return_object() { return *this; }
#else
    auto get_return_object() { return coro_handle::from_promise(*this); }
#endif
    std::suspend_always initial_suspend() { return {}; }                    // Это то же самое, что и return std::suspend_always{};
    std::suspend_always final_suspend() noexcept { return {}; }
    void return_void() {}
    void unhandled_exception() { std::terminate(); }
    std::suspend_always yield_value(const T &val) {
      value = std::addressof(val);                                          // (1). Сохраняем указатель на значение.
      return {};                                                            //      Адрес на постоянное место хранения в куче, где лежит корутинный объект.
    }
  };

  using coro_handle = std::coroutine_handle<promise_type>;

  struct iterator {                                                         // (2). Добавили итератор
    using iterator_category = std::input_iterator_tag;
    using value_type = T;
    using difference_type = ptrdiff_t;
    using pointer = const T *;
    using reference = const T &;

    coro_handle handle;                                                     // (3). Итератор хранит handle
    iterator(coro_handle h) : handle(h) {}

    iterator &operator++() {
      handle.resume();                                                      // (4). Переход к следующему значению в operator++
      if (handle.done())
        handle = nullptr;
      return *this;
    }

    T const &operator*() const { return *handle.promise().value; }
    T const *operator->() const { return handle.promise().value; }
    auto operator<=>(const iterator &rhs) const noexcept = default;
  };

  range_gen(promise_type &promise) : handle_(coro_handle::from_promise(promise)) {}
  range_gen(coro_handle h) : handle_(h) {}
  range_gen(const range_gen &) = delete;
  range_gen &operator=(const range_gen &other) = delete;
  range_gen(range_gen &&rhs) : handle_(rhs.handle_) {
    std::cout << "range_gen(range_gen&& rhs)\n";
    rhs.handle_ = nullptr;
  }
  range_gen &operator=(range_gen &&rhs) {
    std::cout << "range_gen &operator=(range_gen&& rhs)\n";
    if (this != &rhs) {
      handle_ = rhs.handle;
      rhs.handle = nullptr;
    }
    return *this;
  }

  ~range_gen() {
    if (handle_)
      handle_.destroy();
  }

  iterator begin() {                                    // (5). Добавили метод begin()
    if (!handle_)
      return iterator{nullptr};
    handle_.resume();
    if (handle_.done())
      return iterator{nullptr};
    return handle_;
  }

  iterator end() { return iterator{nullptr}; }          // (6). Добавили метод end(). Nullptr - это естестнный optional.

private:
  coro_handle handle_;
};

}

namespace {

template <typename T> range_gen<T> sequence(T start, T fin, T step) {
  for (T num = start; num < fin; num += step)
    co_yield num;
}

}

TEST(coroutines, range_based) {
  int J = 5;
  for (int I : sequence(5, 20, 3)) {
    EXPECT_EQ(I, J);
    J += 3;
  }
}
