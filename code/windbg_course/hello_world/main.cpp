#include <iostream>
#include <string>

struct SimpleStruct
{
    int a;
    char b;
    float c;
    int d;
};

struct ComplexStruct
{
    SimpleStruct ss;
    SimpleStruct* ssPtr;
};

int ga = 100;
int gb = 200;

void foo(std::string str)
{
    std::cout << "foo: " << str << "\n";
}

int main()
{
    const char* str = "hello world";
    int c = ga + gb;
    foo(str);

    SimpleStruct simpleStruct{777, 'x', 66.6, 100};
    SimpleStruct* simpleStructPtr = &simpleStruct;
    ComplexStruct complexStruct{simpleStruct, simpleStructPtr};

    foo("goodbye");

    std::cout << str << c << "\n";
    //_asm int 3;
    std::cout << str << "\n";
    return 0;
}