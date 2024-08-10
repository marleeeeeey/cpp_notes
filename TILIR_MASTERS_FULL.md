- [Interlude](#interlude)
  - [Стандартные преобразования: lvalue to rvalue, array to pointer, function to function pointer](#стандартные-преобразования-lvalue-to-rvalue-array-to-pointer-function-to-function-pointer)
  - [Побочные эффекты и asm](#побочные-эффекты-и-asm)
  - [Проблема `C-строк`](#проблема-c-строк)
  - [`std::string_view` (C++17)](#stdstring_view-c17)
  - [Идиома COW (Copy-On-Write) для `std::string` провалилась](#идиома-cow-copy-on-write-для-stdstring-провалилась)
  - [SSO (Small String Optimization) for `std::string`](#sso-small-string-optimization-for-stdstring)
- [Шаблоны функций](#шаблоны-функций)
  - [Создаем шаблонный метод `do_nth_power` с концептами](#создаем-шаблонный-метод-do_nth_power-с-концептами)
  - [Управление инстанцированием](#управление-инстанцированием)
  - [Правила инстанцирования](#правила-инстанцирования)
  - [`Non-type parameters`](#non-type-parameters)
  - [Шаблонные параметры по умолчанию](#шаблонные-параметры-по-умолчанию)
  - [Пишем правильный оператор сравнения для `basic_string`](#пишем-правильный-оператор-сравнения-для-basic_string)
  - [Идея построения цепочки преобразований](#идея-построения-цепочки-преобразований)

## Interlude

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

## Шаблоны функций

### Создаем шаблонный метод `do_nth_power` с концептами

- [code/tilir_masters/02_10_nth_power.cpp](code/tilir_masters/02_10_nth_power.cpp)
- [code/tilir_masters/02_12_nth_power_default_id_traits.cpp](code/tilir_masters/02_12_nth_power_default_id_traits.cpp)
- [code/tilir_masters/02_14_nth_power_concepts.cpp](code/tilir_masters/02_14_nth_power_concepts.cpp)

### Управление инстанцированием

- `Инстанцирование` - это процесс порождения экземпляра специализации. Может быть **явным** или **неявным**.
  - Инстанцирование может быть **явно запрещено** в этой единице трансляции: `extern template int max<int>(int, int);`.
  - Инстанцирование может быть **явно вызывано**: `template int max<int>(int, int);`.
- Эта техника может использоваться для уменьшения размера объектных файлов при инстанцировании тяжелых функций.
- https://github.com/tilir/cpp-masters/tree/master/functempls/instantiations-demo

```cpp
// max.hpp
template <typename T>[[gnu::noinline]] T max(T x, T y) { return (x > y) ? x : y; }
extern template int max<int>(int, int); // block instancing everywhere  <===

// main.cpp
template int max<int>(int, int); // force instancing here               <===

// maxuser1.cpp
#include "max.hpp"
int main() { return max<int>(1, 2); }

// maxuser2.cpp
#include "max.hpp"
int main() { return max<int>(3, 4); }
```

### Правила инстанцирования

- https://youtu.be/FshTrPe_Woc?t=1840
- [code/tilir_masters/02_18_instantiation_rules.cpp](code/tilir_masters/02_18_instantiation_rules.cpp)
- Явное инстанцирование единожды в программе.
- Явная специализация единожды в программе.
- Явное **инстанцирование должно следовать за явной специализацией**.
- Нарушение приводит к **IFNDR** (**Ill-formed, no diagnostic required**).
- **IFNDR** - это такая ошибка, когда компилятор не обязан делать диагностику. Аналогично ситуации, когда вы забыли поставить скобку.

```cpp
template <typename T> T max(T x, T y) { return x > y ? x : y; }

template int max<int>(int, int); // error: explicit specialization of 'max<int>' after instantiation

template <> int max<int>(int x, int y) { return x > y ? x : y; } // <===
```

### `Non-type parameters`

- [code/tilir_masters/02_20_non_type_parameters.cpp](code/tilir_masters/02_20_non_type_parameters.cpp)
- `non-type template parameter` могут быть:
  - Скалярные типы.
  - Левые ссылки.
  - Структуры, у которых все поля и базовые классы public и не mutable.

- Проще говоря, все должно быть **compile-time known**.
- `non-type template parameter` можно также **параметризовать указателями** на `nullptr`, на `глобальную память` или `статические объекты`.

```cpp
struct Pair {
  int x = 1, y = 1;
};

template <int N, int *PN, int &RN, Pair P> int foo() {
  return N + *PN + RN + P.x + P.y;
}

constexpr Pair p;
int x = 1;
int y = 1;

TEST(nontypes, foo) {
  int res = foo<2, &x, y, p>();
  EXPECT_EQ(res, 2 + 1 + 1 + 1 + 1);
}
```

### Шаблонные параметры по умолчанию

- [code/tilir_masters/02_22_template_default_params.cpp](code/tilir_masters/02_22_template_default_params.cpp)

```cpp
template <typename T = double>  // Defaults for type
double foo(T x = 1.5)           // Defaults for value
{
    return x;
}

TEST(deduce, context)
{
    double v0 = foo(2.0);
    EXPECT_EQ(v0, 2.0);
    double v1 = foo<int>();
    EXPECT_EQ(v1, 1);
    double v2 = foo(); // <=== works well with default for type and value
    EXPECT_EQ(v2, 1.5);
}
```

- Можно использовать слово `auto` для автоматического вывода типа.
- [code/tilir_masters/02_24_template_auto_type.cpp](code/tilir_masters/02_24_template_auto_type.cpp)

```cpp
template <auto n> // <=== auto for type deduction
int foo() { return n; }
```

### Пишем правильный оператор сравнения для `basic_string`

```cpp
template <typename CharT, typename Traits = std::char_traits<CharT>, typename Allocator = std::allocator<CharT>>
bool operator==(const basic_string<CharT, Traits, Allocator>& lhs,
                const basic_string<CharT, Traits, Allocator>& rhs) {
    return lhs.compare(rhs) == 0;
}

template <typename CharT, typename Traits, typename Allocator>
bool operator==(const CharT* lhs, const basic_string<CharT, Traits, Allocator>& rhs) {
    return rhs.compare(lhs) == 0;
}

template <typename CharT, typename Traits, typename Allocator>
bool operator==(const basic_string<CharT, Traits, Allocator>& lhs, const CharT* rhs) {
    return lhs.compare(rhs) == 0;
}
```

### Идея построения цепочки преобразований

- [code/tilir_masters/02_26_chain_of_casts.cpp](code/tilir_masters/02_26_chain_of_casts.cpp)
- С наивной точки зрения цепочку преобразований входят:
  - С высшим приоритетом: **стандартные преобразования**.
  - Немного ниже: **пользовательские преобразования**.
  - С низшим приоритетом: **троеточия**.
- В любой цепочке преобразований может быть **только одно пользовательское преобразование**.

```
| Conversion                         | Category                  | Rank        |
| ---------------------------------- | ------------------------- | ----------- |
| No conversions required            | Identity                  | Identity    |
| Lvalue-to-rvalue conversion        | Lvalue Transformation     | Exact Match |
| Array-to-pointer conversion        | Lvalue Transformation     | Exact Match |
| Function-to-pointer conversion     | Lvalue Transformation     | Exact Match |
| Qualification conversions          | Qualification Adjustment  | Exact Match |
| Function pointer conversion        | Qualification Adjustment  | Exact Match |
| Integral promotions                | Promotion                 | Promotion   |
| Floating-point promotion           | Promotion                 | Promotion   |
| Integral conversions               | Conversion                | Conversion  |
| Floating-point conversions         | Conversion                | Conversion  |
| Floating-integral conversions      | Conversion                | Conversion  |
| Pointer conversions                | Conversion                | Conversion  |
| Pointer-to-member conversions      | Conversion                | Conversion  |
| Boolean conversions                | Conversion                | Conversion  |
```
