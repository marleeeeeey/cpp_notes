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
    ~A() { std::cout << "dctor" << std::endl; }
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

template <typename Fun, typename... Arg>
decltype(auto) transparent_variadic(Fun&& fun, Arg&&... arg)
{
    return std::forward<Fun>(fun)(std::forward<Arg>(arg)...);
}

int main()
{
    {
        A a = no_transparent([](A a) { return a; }, A{});
        (void)a;
        std::cout << "---\n";
    }
    {
        A b = transparent([](A a) { return a; }, A{});
        (void)b;
        std::cout << "---\n";
    }
    {
        auto foo = [](int x, double y, std::string z)
        {
            std::cout << x << " " << y << " " << z << std::endl;
        };
        transparent_variadic(foo, 10, 10.3, "qwer");
        std::cout << "---\n";
    }
    {
        auto foo2 = [](A&& x, A&& y, A&& z) {
        };
        transparent_variadic(foo2, A{}, A{}, A{});
        std::cout << "---\n";
    }
}