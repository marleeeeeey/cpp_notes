
#include <iostream>
#include <string>

// clang-format off

struct A
{
    std::string name;
    A(std::string name) : name(name) {}
    void print() { std::cout << name << std::endl; }
    virtual ~A() = default;
};

struct B : virtual public A
{
    B() : A("B") {}
};

struct C : virtual public A
{
    C() : A("C") {}
};

struct D : public B, public C
{
    D() : A("D"), B(), C() {}
};

int main()
{
    D d;
    d.print();

    B* b = &d;
    b->print();

    C* c = &d;
    c->print();

    A* a = &d;
    a->print();

#if FAILED_CODE
    D* d2 = b;                      // error: cannot initialize a variable of type 'D *' with an lvalue of type 'B *'
    B* b2 = &a;                     // error: cannot initialize a variable of type 'B *' with an rvalue of type 'A **'
    B* b2 = static_cast<B*>(a);     // error: cannot cast 'A *' to 'B *' via virtual base 'A'
    C* c2 = static_cast<C*>(b);     // error: static_cast from 'B *' to 'C *', which are not related by inheritance, is not allowed
#endif

    D* d2 = static_cast<D*>(b);
    d2->print();

    void* unknown = dynamic_cast<void*>(a);
    if (unknown)
        std::cout << "unknown" << std::endl;

    B* b2 = dynamic_cast<B*>(a);
    b2->print();

    C* c2 = dynamic_cast<C*>(b);
    c2->print();
}