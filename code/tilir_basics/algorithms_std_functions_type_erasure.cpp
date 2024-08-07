#include <functional>
#include <iostream>

#define BUILD_FAILS 0

// clang-format off

using VVTy = std::function<void(void)>;

struct Foo
{
    int x = 5;
#if BUILD_FAILS
    VVTy xplusbad1 = [x] mutable { x += 3; } (); // FAIL
    VVTy xplusbad2 = [&x] { x += 3; } (); // FAIL
    VVTy xplus1 = [=] { x += 3; }; // not exactly ok (deprecated in C++20)
#endif
    VVTy xplus2 = [&] { x += 3; };    // OK
    VVTy xplus3 = [this] { x += 3; }; // OK
};

// clang-format on

int main()
{
    Foo f;
#if BUILD_FAILS
    f.xplus1();
#endif
    f.xplus2();
    f.xplus3();
    std::cout << f.x << std::endl;
}