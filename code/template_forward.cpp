#include <iostream>
#include <utility>

// clang-format off
struct A
{
    explicit A() { std::cout << "ctor" << std::endl; }
    A(const A&) { std::cout << "copy ctor" << std::endl; }
    A(A&&) { std::cout << "move ctor" << std::endl; }
    A& operator=(const A&) { std::cout << "copy assign" << std::endl; return *this; }
    A& operator=(A&&) { std::cout << "move assign" << std::endl; return *this; }
};
// clang-format on

template <typename Fun, typename Arg>
decltype(auto) no_transparent(Fun fun, Arg&& arg)
{
    return fun(arg); // arg always copied
}

template <typename Fun, typename Arg>
decltype(auto) transparent(Fun fun, Arg&& arg)
{
    return fun(std::forward<Arg>(arg)); // arg may be moved
}

int main()
{
    A a = no_transparent([](A a) { return a; }, A{});
    std::cout << "---\n";
    A b = transparent([](A a) { return a; }, A{});
    std::cout << "---\n";
}