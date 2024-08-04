#include <iostream>

// clang-format off

struct Foo
{
    int x;
    void func()
    {
        [&a = this->x] mutable { a+= 3; } ();

        #if 0
        [x] mutable { x += 3; } (); // FAIL
        [&x] { x += 3; } (); // FAIL

        // implicit capture of 'this' with a capture default of '=' is deprecated in C++20
        // Потому что все остальное, что вы захватите через =, будет иметь другое время жизни в отличие от this.
        [=] { x += 3; } ();
        #endif
        [&] { x += 3; } (); // OK
        [this] { x += 3; } (); // OK
    }
};

// clang-format on

int main()
{
    Foo foo;
    foo.func();
    std::cout << foo.x << std::endl;
}