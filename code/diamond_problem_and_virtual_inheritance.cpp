#include <iostream>

// Uncomment/Comment the following line to see the difference
#define VIRTUAL

struct A
{
    A() { std::cout << "A constructor " << this << std::endl; }
};

struct BA :
#ifdef VIRTUAL
  virtual
#endif
  A
{
    BA() { std::cout << "BA constructor " << this << std::endl; }
};

struct CA :
#ifdef VIRTUAL
  virtual
#endif
  A
{
    CA() { std::cout << "CA constructor " << this << std::endl; }
};

struct DCBA : BA, CA
{
    DCBA() { std::cout << "D constructor " << this << std::endl; }
};

int main()
{
    DCBA* d = new DCBA();
    std::cout << "d: " << d << " typeid: " << typeid( d ).name() << std::endl;
    BA* ba = static_cast<BA*>( d );
    std::cout << "ba: " << ba << " typeid: " << typeid( ba ).name() << std::endl;
    CA* ca = static_cast<CA*>( d ); // Static cast may change the address
    std::cout << "ca: " << ca << " typeid: " << typeid( ca ).name() << std::endl;
#ifdef VIRTUAL
    A* a = static_cast<A*>( d ); // Static cast is not allowed in this case
    std::cout << "a: " << a << " typeid: " << typeid( a ).name() << std::endl;
#endif
}