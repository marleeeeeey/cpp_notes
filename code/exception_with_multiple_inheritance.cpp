#include <exception>
#include <iostream>

// USE_VIRTUAL_INHERITANCE does not affect the output
#define USE_VIRTUAL_INHERITANCE 1

struct B :
#if USE_VIRTUAL_INHERITANCE
  virtual
#endif
  std::exception
{
    B() { std::cout << "B constructor " << this << std::endl; }
    ~B() { std::cout << "B destructor " << this << std::endl; }
};

struct C :
#if USE_VIRTUAL_INHERITANCE
  virtual
#endif
  std::exception
{
    C() { std::cout << "C constructor " << this << std::endl; }
    ~C() { std::cout << "C destructor " << this << std::endl; }
};

struct D : B, C
{
    D() { std::cout << "D constructor " << this << std::endl; }
    ~D() { std::cout << "D destructor " << this << std::endl; }
};

int main()
{
    try
    {
        throw D();
    }
    catch (std::exception const& e)
    {
        std::cout << "Caught an exception: " << e.what() << std::endl;
    }
    catch (...)
    {
        std::cout << "Caught an unknown exception" << std::endl;
    }
}