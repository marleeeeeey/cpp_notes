#include <iostream>
#include <memory>
#include <sstream>

#include "gtest/gtest.h"

// clang-format off

#define CPP_23 0

namespace {

struct object_t {
  virtual void draw(std::ostream &, size_t pos) const = 0;
  virtual std::unique_ptr<object_t> clone() const = 0;
  virtual ~object_t() {}
};

template <typename Base, typename Derived> struct MixClonable : public Base  {
  std::unique_ptr<Base> clone() const override {
    return std::unique_ptr<Base>(new Derived(static_cast<Derived const &>(*this)));
  }
};

struct int_t : public MixClonable<object_t, int_t> {
  int data;
  int_t(int data): data(data) {}

  void draw(std::ostream &os, size_t pos) const override {
    os << std::string(pos, ' ') << data;
  }
};

#if CPP_23
template <typename Base> struct MixClonable : public Base {
template <typename Self>
std::unique_ptr<Base> clone(this Self&& self) const override {
    return std::unique_ptr<Base>(new Self(self));
}
};

struct int_t : public MixClonable<object_t> {
int data;
    void draw(std::ostream &os, size_t pos) const override
    { os << std::string(pos, ' ') << data; }
};
#endif

}

TEST(rtpoly, virtintf) {
  std::ostringstream os;
  auto i = std::unique_ptr<object_t>(new int_t(42));
  auto j = i->clone();
  i->draw(os, 0);
  j->draw(os, 0);
  EXPECT_EQ(os.str(), "4242");
}