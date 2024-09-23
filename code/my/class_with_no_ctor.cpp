#include <cassert>
#include <iostream>

/*
Checking if the object is created without a constructor.
=> If no constructor is defined, the compiler will generate a default constructor.
*/

class A
{
public:
    virtual void msg() { std::cout << "A" << this << std::endl; }
};

class B : public A
{
public:
    virtual void msg() { std::cout << "B" << this << std::endl; }
};

void foo(A a)
{
    a.msg();
}

void bar(A& a)
{
    a.msg();
}

int main()
{
    B b;
    b.msg();
    foo(b); // call A::A()
    bar(b);
}