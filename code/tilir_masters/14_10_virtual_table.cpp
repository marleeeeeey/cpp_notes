#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory_resource>

struct Base
{
    virtual void foo() = 0;
    virtual ~Base() {}
};

struct Derived : Base
{
    void foo() override;
};

void call(Base& b)
{
    b.foo();
}

void buz(Base&);

void bar()
{
    Derived d;
    buz(d);
}