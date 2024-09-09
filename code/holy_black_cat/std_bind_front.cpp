#include <cassert>
#include <functional>

int minus(int a, int b)
{
    return a - b;
}

int main()
{
    auto fifty_minus = std::bind_front(minus, 50); // <<=== std::bind_front

    // equivalent to: minus(50, 3) == 47
    assert(fifty_minus(3) == 47);
}