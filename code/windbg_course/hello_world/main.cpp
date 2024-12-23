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
    std::cout << "foo : " << str << "\n";
}

void foo2(std::string str)
{
    std::cout << "foo2: " << str << "\n";
}

void foo3(std::string str)
{
    std::cout << "foo3: " << str << "\n";
}

int main()
{
    const char* str = "hello world";
    int c = ga + gb;
    ga = 333;
    foo(str);
    foo2(str);
    foo3(str);

    SimpleStruct simpleStruct{777, 'x', 66.6, 100};
    SimpleStruct* simpleStructPtr = &simpleStruct;
    ComplexStruct complexStruct{simpleStruct, simpleStructPtr};

    ga = 777;
    foo("goodbye");
    foo2("goodbye");
    foo3("goodbye");

    std::cout << str << c << "\n";
    //_asm int 3;
    std::cout << str << "\n";
    return 0;
}