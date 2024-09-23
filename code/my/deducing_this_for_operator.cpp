#include <iostream>

/*
Trying deducing this technique for operator overloading.
See more info in the file: 2024-08-08_0010_HolyBlackCat.md
*/

#define USE_DEDUCING_THIS 1

class A
{
    int* a;
public:
    A(int* a_) : a(a_) { *a += 100; }

#if USE_DEDUCING_THIS
    template <typename Self>
    operator decltype(std::declval<Self>().a)(this Self && self)
    {
        return self.a;
    }
#else
    operator const int*() const { return a; }
    operator int*() { return a; }
#endif
};

int main()
{
    int a = 0;
    const A a_(&a);
    std::cout << "a=" << a << std::endl;
    const int* p = a_;
    std::cout << "p=" << *p << std::endl;
}