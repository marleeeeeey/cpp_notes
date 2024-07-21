#include <iostream>
#include <typeinfo>

// Enable/Disable this line to see the difference
#define USE_POLIMORFIC_TYPE 0

struct S
{
    virtual void f();
};

int main()
{
#if USE_POLIMORFIC_TYPE
    S* a = nullptr;
#else
    int* a = nullptr;
#endif
    try
    {
        std::cout << typeid(*a).name() << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Caught an exception: " << e.what() << std::endl;
    }
}