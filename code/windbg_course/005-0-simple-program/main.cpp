#include <iostream>

int global = 100;

int main()
{
    const char* str = "hello world";
    std::cout << str;
    _asm int 3;
    std::cout << str;
    return 0;
}