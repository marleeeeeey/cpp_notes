#include <cstddef>
#include <iostream>

// https://godbolt.org/z/TT7Ebjczf

int foo()
{
    volatile int a = 10;
    int b = a;
    return b;
}

int* bar()
{
    volatile std::nullptr_t a = nullptr;
    int* b;
    b = a;
    return b;
}

// clang asm:
// foo():
//         mov     dword ptr [rsp - 4], 10
//         mov     eax, dword ptr [rsp - 4]
//         ret
// bar():                                       // ТУТ ДРУГОЙ АССЕМБЛЕР
//         mov     qword ptr [rsp - 8], 0
//         xor     eax, eax
//         ret
// -------------------------------------------------------------------------
// gcc asm
// foo():
//         mov     DWORD PTR [rsp-4], 10
//         mov     eax, DWORD PTR [rsp-4]
//         ret
// bar():                                       // ТУТ ДРУГОЙ АССЕМБЛЕР
//         mov     QWORD PTR [rsp-8], 0
//         mov     rax, QWORD PTR [rsp-8]
//         xor     eax, eax
//         ret

int main()
{}