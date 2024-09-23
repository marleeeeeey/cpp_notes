#include <iostream>

// clang-format off

/*
Investigating the size of a class after interviewing with a company.

- sizeof() depends on the alignment of the members and the class itself
- vtable pointer is added to the class size if class has virtual functions
- when you have multiple inheritance from classes with virtual functions
   several vtable pointers are added to the class size
- I can't understand why sizeof(G) is 24, I would expect 32 (see example below) <===
*/

class A
{
public:
    char ch;        // ---- ---+
    int i;          // ---- ++++
    long long ll;   // ++++ ++++ // longest type used as source of aligment
};

class B
{
public:
    int i; // ++++
};

#pragma pack(1)
class A1
{
public:
    char ch;    // +
    int i;      // ++++
};

#pragma pack(2)
class A2
{
public:
    char ch;    // -+
    int i;      // ++++
};

#pragma pack(1)

// sizeof(C) = 8 on x64
class C
{
    virtual void f1() = 0;
};

class D
{
    virtual void f2() = 0;
};

class E
{
    virtual void f3() = 0;
};

// sizeof(F) = 24
class F : public C, public D, public E
{};

// sizeof(G) = 24 ???
class G : public C, public D, public E
{
    virtual void f4() = 0;
};

int main()
{
    std::cout << "sizeof(A )=" << sizeof(A) << std::endl;
    std::cout << "sizeof(B )=" << sizeof(B) << std::endl;
    std::cout << "sizeof(A1)=" << sizeof(A1) << std::endl;
    std::cout << "sizeof(A2)=" << sizeof(A2) << std::endl;
    std::cout << "sizeof(C )=" << sizeof(C) << std::endl;
    std::cout << "sizeof(D )=" << sizeof(D) << std::endl;
    std::cout << "sizeof(E )=" << sizeof(E) << std::endl;
    std::cout << "sizeof(F )=" << sizeof(F) << std::endl;
    std::cout << "sizeof(G )=" << sizeof(G) << std::endl;
}