#include <utility>

#define ENABLE_FAILS 0

struct Foo
{
    Foo() = delete;
    int bar() { return 1; }
};

int main()
{
#if ENABLE_FAILS
    decltype(Foo()); // error: call to deleted constructor of 'Foo'
#endif
    decltype(std::declval<Foo>().bar()) a;
    (void)a;
}