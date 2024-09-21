// https://en.cppreference.com/w/cpp/language/value_category

#include <iostream>

struct S
{
    S() : m{42} {}
    S(int a) : m{a} {}
    int m;
};

int main()
{
    S s;

    // Expression `S{}` is prvalue
    // May appear on the right-hand side of an assignment expression
    s = S{};

    std::cout << s.m << '\n';

    // Expression `S{}` is prvalue
    // Can be used on the left-hand side too
    std::cout << (S{} = S{7}).m << '\n';
}