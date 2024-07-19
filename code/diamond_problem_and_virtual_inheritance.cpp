#include <iostream>

// Uncomment/Comment the following lines to see the difference
#define USE_VIRTUAL_INHERITANCE
#define IMPLEMENT_VIRTUAL_DESTRUCTOR

struct A
{
    A() { std::cout << "A constructor " << this << std::endl; }
#ifdef IMPLEMENT_VIRTUAL_DESTRUCTOR
    virtual ~A() = default;
#endif
};

struct BA :
#ifdef USE_VIRTUAL_INHERITANCE
  virtual
#endif
  A
{
    BA() { std::cout << "BA constructor " << this << std::endl; }
};

struct CA :
#ifdef USE_VIRTUAL_INHERITANCE
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
    std::cout << "d: " << d << " | dynamic typeid: " << typeid( *d ).name()
              << " | static typeid: " << typeid( d ).name() << std::endl;
    BA* ba = static_cast<BA*>( d );
    std::cout << "ba: " << ba << " | dynamic typeid: " << typeid( *ba ).name()
              << " | static typeid: " << typeid( ba ).name() << std::endl;
    CA* ca = static_cast<CA*>( d ); // Static cast may change the address
    std::cout << "ca: " << ca << " | dynamic typeid: " << typeid( *ca ).name()
              << " | static typeid: " << typeid( ca ).name() << std::endl;
#ifdef USE_VIRTUAL_INHERITANCE
    A* a = static_cast<A*>( d ); // Static cast is not allowed in this case
    std::cout << "a: " << a << " | dynamic typeid: " << typeid( *a ).name()
              << " | static typeid: " << typeid( a ).name() << std::endl;
#endif
}