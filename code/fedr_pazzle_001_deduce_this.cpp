#include <iostream>

struct A
{
    int f()
    {
        std::cout << "A::f()" << std::endl;
        return 1;
    }
};

struct B : A
{
    using A::f;
    int f(this A)
    {
        std::cout << "B::f(this A)" << std::endl;
        return 2;
    }
};

int main()
{
    B{}.f();
}