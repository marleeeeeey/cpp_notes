### Стандартные преобразования: lvalue to rvalue, array to pointer, function to function pointer

- Последовательность стандартных преобразований всегда начинается с не более чем одного из трех преобразований.

```cpp
  int a = 5, b; b = a + 2; // lvalue to rvalue: `a` была lvalue, но в выражении `a + 2` она преобразуется в rvalue

  int a[10], int *b; b = a; // array to pointer

  int foo(int);
  int (*b)(int);
  b = foo; // function to function pointer
```

### Побочные эффекты и asm

- https://godbolt.org/z/TT7Ebjczf
- [code/tilir_masters/01_10_side_effects.cpp](code/tilir_masters/01_10_side_effects.cpp)
- Компилятор должен сохранять порядок побочных эффектов.

```cpp

int* bar()
{
    volatile std::nullptr_t a = nullptr;
    int* b;
    b = a;
    return b;
}

// clang asm:
// bar():
//         mov     qword ptr [rsp - 8], 0
//         xor     eax, eax
//         ret
// -------------------------------------------------------------------------
// gcc asm
// bar():
//         mov     QWORD PTR [rsp-8], 0
//         mov     rax, QWORD PTR [rsp-8]
//         xor     eax, eax
//         ret

```

### Проблема `C-строк`

- В C строках нет инварианта на размер строки. С этим связано много уязвимостей. Поэтому и решили придумать C++ с классами, которые помогают защитить инвариант.

### `std::string_view` (C++17)

- `std::string_view` реализует `reference семантику`, потому что `std::string_view` не является владельцем данных, на которые она указывает,
- а `std::string` владеет данными, и это называется `value-семантикой`.
- `std::string_view` реализует набор удобных операций для управления окном из символов. Можно уменьшать, расширять окно, копировать, сравнивать, искать.

```cpp
// Здесь нет ни heap indirection ни создания временного объекта

static const std::string_view kName = "FOO";
// .....
int foo(const std::string_view &arg);
// .....
foo(kName);
```

### Идиома COW (Copy-On-Write) для `std::string` провалилась

- Плюсы
  - Экономия памяти
  - Дешёвое копирование (просто инкремент счётчика ссылок)
  - Меньше аллокаций и удалений в куче => прирост производительности
- Минусы
  - Лишний уровень косвенности
  - Вирусное проникновение копирования во все модифицирующие операции
  - Проблемы thread safety (Multithread COW disease)
  - Однако есть соображение, которое рушит баланс. Это **инвалидация указателей**

### SSO (Small String Optimization) for `std::string`

```
<-------------------- 32 bytes ------------------>
┌─────────────┬─────────────┬───────────┬────────┐
│ data: points│  size > 15  │ capacity  │ padding│
│ to heap     │             │           │        │
│             │             │           │        │
└─────────────┴─────────────┴───────────┴────────┘

<-------------------- 32 bytes ------------------>
                            <----- 16 bytes ----->
┌─────────────┬─────────────┬────────────────────┐
│ data: points│ size <= 15  │        small       │
│ to small    │             │        string      │
│ string      │             │                    │
└─────────────┴─────────────┴────────────────────┘
```

- Это решение позволяет избежать потерь времени при доступе
- Но уменьшает размер строки, которую можно хранить в SSO
- Пример с хорошей SSO строкой. Но без TypeTraits и Аллокаторов:

```cpp
template <typename CharT> class basic_string {
    CharT *data;
    size_t size;
    union {
        size_t capacity;
        enum { SZ = (sizeof(data) + 2*sizeof(size_t) + 31) / 32 };
        CharT small_str[SZ];
    } sso;
public:
    // тут все его 89 методов
};
```
