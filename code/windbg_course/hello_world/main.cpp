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


void updateGlobals()
{
    ga++;
    gb--;
    std::cout << "123" << std::endl;
}


void foo(const char * str)
{
    std::cout << "foo : " << str << "\n";
    updateGlobals();
}

void foo2(const char* str)
{
    std::cout << "foo2: " << str << "\n";
    updateGlobals();
}

void __stdcall foo3(const char* str)
{
    std::cout << "foo3: " << str << "\n";
    updateGlobals();
}

void __stdcall bar2(int a, int b, int c)
{
    a + b + c;
}

int bar(int a, int b, int c, int d)
{
    int x = 1;
    int y = 2;
    int z = 3;
    bar2(a + x, b + y, c + z);
    return 0;
}

int main()
{
    bar(100, 200, 300, 400);
    return 0;
}

int main2()
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

    //std::cout << str << c << "\n";
    ////_asm int 3;
    //std::cout << str << "\n";
    return 0;
}