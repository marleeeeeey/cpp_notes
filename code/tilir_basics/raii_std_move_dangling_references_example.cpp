#include <iostream>
#include <string>
#include <utility>

// OK
int& foo(int& v)
{
    return v;
}

// https://youtu.be/_mLDaU4wSOo?t=2732
std::string&& bar(std::string&& v) // Here is rvalue object created.
{
    std::cout << "[bar] " << &v << "=" << v << std::endl;
    return std::move(v);
}

int main()
{
    auto&& x = std::move(bar("hello")); // UB: Dangling reference. Object `std::string&& v` destroyed here.
    std::cout << "[main] " << &x << "=" << x << std::endl;
}
