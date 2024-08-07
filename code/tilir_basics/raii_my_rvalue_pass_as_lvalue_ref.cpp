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

void foo(const A& lvalue)
{
    (void)lvalue;
}

void bar(A&& lvalue)
{
    (void)lvalue;
}

void nik(A& lvalue)
{
    (void)lvalue;
}

int main()
{
    foo(A{}); // создается временный объект, который привязывается к `const int&`
    // nik(A{}); // Compile error:
    A lvalue{};
    // bar(lvalue); // Compilation error.
    bar(std::move(lvalue));
}