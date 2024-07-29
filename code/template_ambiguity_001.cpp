#include <cstdlib>

// clang-format off

template <typename T> struct Base {
    void exit(int i) {}
};

template<typename T> struct Derived : Base<T> {
    void foo() {
        exit(1); // Call external exit
    }
};

template<typename T> struct Derived2 : Base<T> {
    void foo() {
        this->exit(1); // Call exit from Base
    }
};

// clang-format on

int main()
{
    Derived<int> d1;
    Derived2<int> d2;
    d1.foo();
    d2.foo();
}