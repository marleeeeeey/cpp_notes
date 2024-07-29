#include <iostream>

// clang-format off
struct A
{
    explicit A() { std::cout << "ctor" << std::endl; }
    A(const A&) { std::cout << "copy ctor" << std::endl; }
    A(A&&) { std::cout << "move ctor" << std::endl; }
    A& operator=(const A&) { std::cout << "copy assign" << std::endl; return *this; }
    A& operator=(A&&) { std::cout << "move assign" << std::endl; return *this; }
    ~A() { std::cout << "dctor" << std::endl; }
};
// clang-format on

template <typename T>
void foo(const T& lvalue)
{
    (void)lvalue;
}

int main()
{
    foo(A{});
}