#include <iostream>

// Uncomment/Comment the following line to see the difference
#define CATCH_BY_REFERENCE 0
#define USE_CROSS_CALL 1

struct A
{
    A() { std::cout << "A constructor " << this << std::endl; }
    A(const A&) { std::cout << "A copy constructor " << this << std::endl; }
    ~A() { std::cout << "A destructor " << this << std::endl; }
};

struct B : A
{
    B() { std::cout << "B constructor " << this << std::endl; }
    ~B() { std::cout << "B destructor " << this << std::endl; }
};

int foo()
{
    throw B();
}

int main()
{
    try
    {
#if USE_CROSS_CALL
        foo();
#else
        throw B();
#endif
    }
#if CATCH_BY_REFERENCE
    catch (A& A)
#else
    catch (A A)
#endif
    {
        std::cout << "Caught an A" << std::endl;
    }
    catch (B B)
    {
        std::cout << "Caught a B" << std::endl;
    }

    std::cout << "--- End of try-catch block ---" << std::endl;

    B();
}
