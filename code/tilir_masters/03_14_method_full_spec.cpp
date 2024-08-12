#include "gtest/gtest.h"

// clang-format off

struct Data {
  template <typename T> T read() const {
    return {};
  }
};

template <typename T> class DataReader {
  const T& source_;
public:
  DataReader(const T& source) : source_(source) {}
  template <typename R> R read();
};

template <typename T>
template <typename R>
R DataReader<T>::read() {
  R res = source_.template read<R>();
  return res;
}

template <> // <===
template <> // <===
std::string DataReader<Data>::read<std::string>() {
  return "S";
}

TEST(partialspec, backward) {
  Data d;
  DataReader<Data> reader(d);
  auto myval = reader.read<int>();
  EXPECT_EQ(myval, 0);
  auto mys = reader.template read<std::string>();
  EXPECT_EQ(mys, "S");
}