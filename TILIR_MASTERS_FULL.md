- [--------------------- 01. Строки ---------------------](#----------------------01-строки----------------------)
- [Interlude](#interlude)
  - [Стандартные преобразования: lvalue to rvalue, array to pointer, function to function pointer](#стандартные-преобразования-lvalue-to-rvalue-array-to-pointer-function-to-function-pointer)
  - [Побочные эффекты и asm](#побочные-эффекты-и-asm)
  - [Проблема `C-строк`](#проблема-c-строк)
  - [`std::string_view` (C++17)](#stdstring_view-c17)
  - [Идиома COW (Copy-On-Write) для `std::string` провалилась](#идиома-cow-copy-on-write-для-stdstring-провалилась)
  - [SSO (Small String Optimization) for `std::string`](#sso-small-string-optimization-for-stdstring)
- [--------------------- 02. Шаблоны функций ---------------------](#----------------------02-шаблоны-функций----------------------)
- [Шаблоны функций](#шаблоны-функций)
  - [Создаем шаблонный метод `do_nth_power` с концептами](#создаем-шаблонный-метод-do_nth_power-с-концептами)
  - [Управление инстанцированием](#управление-инстанцированием)
  - [Правила инстанцирования](#правила-инстанцирования)
  - [`Non-type parameters`](#non-type-parameters)
  - [Шаблонные параметры по умолчанию](#шаблонные-параметры-по-умолчанию)
  - [Пишем правильный оператор сравнения для `basic_string`](#пишем-правильный-оператор-сравнения-для-basic_string)
  - [Идея построения цепочки преобразований](#идея-построения-цепочки-преобразований)
  - [Перегрузка и шаблоны](#перегрузка-и-шаблоны)
  - [Cпециализации не участвуют в перегрузке](#cпециализации-не-участвуют-в-перегрузке)
  - [Компилятор не занимается жадным матчингом в шаблонах](#компилятор-не-занимается-жадным-матчингом-в-шаблонах)
- [--------------------- 03. Шаблоны классов ---------------------](#----------------------03-шаблоны-классов----------------------)
- [Шаблоны классов](#шаблоны-классов)
  - [ODR (One Definition Rule) для классов и функций работает по разному](#odr-one-definition-rule-для-классов-и-функций-работает-по-разному)
  - [Частичная специализация шаблонов (работает только для классов)](#частичная-специализация-шаблонов-работает-только-для-классов)
  - [Частичная специализация не всегда должна иметь меньше или равное количество шаблонов-параметров](#частичная-специализация-не-всегда-должна-иметь-меньше-или-равное-количество-шаблонов-параметров)
  - [Трюк Саттера для создания частичной специализации функции через класс](#трюк-саттера-для-создания-частичной-специализации-функции-через-класс)
  - [Специализация классов только лишь похожа на наследование - она нарушает LSP (Liskov Substitution Principle)](#специализация-классов-только-лишь-похожа-на-наследование---она-нарушает-lsp-liskov-substitution-principle)
- [Специализация методов классов](#специализация-методов-классов)
  - [`.template` используется для разрешения неоднозначности, если мы хотим вызвать шаблонный метод](#template-используется-для-разрешения-неоднозначности-если-мы-хотим-вызвать-шаблонный-метод)
  - [Для специализации шаблонного метода шаблонного класса нужно съедать и параметры класса и параметры метода](#для-специализации-шаблонного-метода-шаблонного-класса-нужно-съедать-и-параметры-класса-и-параметры-метода)
  - [Переходники типов - специализация метода класса по параметру шаблона класса](#переходники-типов---специализация-метода-класса-по-параметру-шаблона-класса)
  - [Переходник типов для имитации частичной специализации функций](#переходник-типов-для-имитации-частичной-специализации-функций)
- [Вывод типов шаблонами классов](#вывод-типов-шаблонами-классов)
  - [Конструкторы классов могут использоваться для вывода типов (С++17)](#конструкторы-классов-могут-использоваться-для-вывода-типов-с17)
  - [`Deduction Hints` - хинты вывода типов могут быть использованы для вывода типов конструкторами классов и агрегатами (С++17)](#deduction-hints---хинты-вывода-типов-могут-быть-использованы-для-вывода-типов-конструкторами-классов-и-агрегатами-с17)
- [Разрешение имен (шаблоны классов)](#разрешение-имен-шаблоны-классов)
  - [Двухфазное разрешение имен (тонкий пример)](#двухфазное-разрешение-имен-тонкий-пример)
  - [Disambiguation (Разрешение неоднозначности): `.template`, `typename`](#disambiguation-разрешение-неоднозначности-template-typename)
  - [Отношение **общий**, **частный** в специализации шаблонных классов](#отношение-общий-частный-в-специализации-шаблонных-классов)
- [--------------------- 04. Модули ---------------------](#----------------------04-модули----------------------)
- [One Definition Rule (ODR)](#one-definition-rule-odr)
  - [Единица трансляции](#единица-трансляции)
  - [Классы связывания](#классы-связывания)
  - [ODR(One Definition Rule)](#odrone-definition-rule)
  - [(1) `non-inline` for ODR](#1-non-inline-for-odr)
  - [(2) `odr-used` for ODR](#2-odr-used-for-odr)
  - [(3) `discarded statement` for ODR](#3-discarded-statement-for-odr)
  - [Предкомпилированные header файлы (первая попытка ускорить компиляцию)](#предкомпилированные-header-файлы-первая-попытка-ускорить-компиляцию)
  - [Модули (C++20) - идеальные предкомпилированные header файлы](#модули-c20---идеальные-предкомпилированные-header-файлы)
  - [Импортируем модуль в модуль](#импортируем-модуль-в-модуль)
  - [Что нельзя экспортировать из модуля](#что-нельзя-экспортировать-из-модуля)
  - [Глобальный фрагмент модуля, в который можно сделать `include`](#глобальный-фрагмент-модуля-в-который-можно-сделать-include)
- [--------------------- 05. SFINAE ---------------------](#----------------------05-sfinae----------------------)
- [SFINAE (Substitution Failure Is Not An Error)](#sfinae-substitution-failure-is-not-an-error)
  - [Можно создавать шаблонные переменные](#можно-создавать-шаблонные-переменные)
  - [SFNIAE unwrapping](#sfniae-unwrapping)
  - [Использование `void_t`, чтобы спросить, если у типа определенный метод (интерфейс)](#использование-void_t-чтобы-спросить-если-у-типа-определенный-метод-интерфейс)
  - [`void_t` — это не шаблон, это алиас. Алиасы имеют некоторые особенности](#void_t--это-не-шаблон-это-алиас-алиасы-имеют-некоторые-особенности)
  - [ENABLE\_IF - условная конструкция для типов](#enable_if---условная-конструкция-для-типов)
- [--------------------- 06. Constexpr ---------------------](#----------------------06-constexpr----------------------)
  - [`if constexpr` - выкидывает ветки ШАБЛОННЫХ инстанцирований](#if-constexpr---выкидывает-ветки-шаблонных-инстанцирований)
  - [`constexpr` функции времени компиляции](#constexpr-функции-времени-компиляции)
  - [`consteval` (C++20)](#consteval-c20)
  - [`constinit` (С++20)](#constinit-с20)
  - [`if consteval` (C++23)](#if-consteval-c23)
  - [Core constant expressions](#core-constant-expressions)

## --------------------- 01. Строки ---------------------

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

## --------------------- 02. Шаблоны функций ---------------------

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
- Выбор пользовательского преобразования зависит от длины хвоста стандартных преобразований. Голова не участвует в конкурсе.

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

### Перегрузка и шаблоны

- Шаблон может выиграть перегрузку. При этом запускается вывод типов.

```cpp
void foo(double x); // 1
template <typename T> void foo(T x); // 2

foo(1); // → несомненно, 2
```

- Для выигрывающего перегрузку шаблона запускается инстанцирование или ищется специализация.
  - Вызов `foo(1)` находит `PrimaryTemplate 2`, понимает, что это тип `int`, видит, что для типа `int` есть специализация, и вызывает `специализацию 3`.

```cpp
template <> void foo<int>(int x); // 3

foo(1); // → что вы думаете?
```

### Cпециализации не участвуют в перегрузке

- Важно помнить: специализации не участвуют в перегрузке.
- Cначала разрешается перегрузка, потом ищется наименее общая специализация.

```cpp
template <typename T> void foo(T); // 1
template <> void foo (int*); // 2
template <typename T> void foo(T*); // 3

int x;
foo(&x); // вызовет [3], хотя [2] подходит лучше
// Но в данном случае (2) не специализирует (3), так как встречается раньше.
```

### Компилятор не занимается жадным матчингом в шаблонах

- Компилятор не занимается жадным матчингом.
- **Компилятор пытается сделать как можно более точный матчинг**.
- Поэтому будет выбрано инстанцирование шаблона 2.

```cpp
template <typename T> void f(T); // 1
template <typename T> void f(T*); // 2

int **a;
foo(a); // → ?
```

## --------------------- 03. Шаблоны классов ---------------------

## Шаблоны классов

### ODR (One Definition Rule) для классов и функций работает по разному

1. **Для функций**: Правило ODR (One Definition Rule) означает, что функция может быть определена **только один раз в пределах всей программы**. Это касается не только тела функции, но и её сигнатуры, что подразумевает наличие одного уникального определения на программу. Если функция определена в нескольких местах, то это может привести к **ошибке компоновки (linker error)**.

2. **Для классов**: ODR работает немного по-другому. Класс **может быть определён в каждой единице трансляции**, в которой он используется, но каждое из этих определений **должно быть идентичным**. Иными словами, все единицы трансляции должны "видеть" одно и то же определение класса. Если определения класса в разных единицах трансляции различаются, это также приведет к нарушению ODR и, следовательно, к **ошибкам на этапе компоновки или выполнения**.

### Частичная специализация шаблонов (работает только для классов)

- *Это простые примеры специализации. А что, если передать `float*, float*`?* (риторический вопрос)
- [code/tilir_masters/03_10_class_spec_example.cpp](code/tilir_masters/03_10_class_spec_example.cpp)

```cpp
template <typename T, typename U> class Foo {}; // 1
template <typename T> class Foo<T, T> {}; // 2
template <typename T> class Foo<T, int> {}; // 3
template <typename T, typename U> class Foo<T*, U*> {}; // 4

Foo<int, float> mif; // соответствует 1
Foo<float, float> mff; // соответствует 2
Foo<float, int> mfi; // соответствует 3
Foo<int*, float*> mp; // соответствует 4
```

### Частичная специализация не всегда должна иметь меньше или равное количество шаблонов-параметров

- Частичная специализация съедает какое-то количество параметров primary шаблона.
- До тех пор, пока она менее специальна в неком смысле, у неё может быть даже **больше** шаблонных параметров.
- Для создания аналога `std::function` мы можем, наоборот, увеличить количество параметров, и это будет более специальный пример.

```cpp
template <typename T> class X;
template <typename R, typename Arg> class X<R(Arg)> {};
```

### Трюк Саттера для создания частичной специализации функции через класс

- [code/tilir_masters/03_12_satters_trick.cpp](code/tilir_masters/03_12_satters_trick.cpp)
- Частичная специализация функций запрещена.
- Можно ли симитировать частичную специализацию функций через частичную специализацию классов?
- Здесь используется то, что статический метод stateless класса мало отличается от свободной функции.

```cpp
template <typename T> struct FImpl;
template <typename T> void f(T t) { FImpl<T>::f(t); }
template <typename T> struct FImpl {
    static void f(T t);
};
```

### Специализация классов только лишь похожа на наследование - она нарушает LSP (Liskov Substitution Principle)

- Можно ли шаблонную специализацию назвать разновидностью наследования?
- Увы, нет. С точки зрения наследования это нарушение LSP. Т.е. "наследник" не может заменить предка.
- Специализация может не иметь ничего общего с полной версией.

```cpp
template <typename T> struct S { void foo (); };
template <> struct S<int> { void bar (); };

S<double> sd; sd.foo();
S<int> si; si.bar();
```

## Специализация методов классов

### `.template` используется для разрешения неоднозначности, если мы хотим вызвать шаблонный метод

- По дефолту все что может быть засчитано как поле класса, будет засчитано как поле класса.
- Поэтому, если мы хотим что-то трактовать не как поле, а как шаблонный метод, то нужно использовать `.template`.

```cpp
template <typename T> class DataReader {
    const T& source_;
public:
    template <typename R> R read(); // <===
};

template <typename T>
template <typename R>
R DataReader<T>::read() {
    R res = source_.template read<R>(); // <===
    return res;
}
```

### Для специализации шаблонного метода шаблонного класса нужно съедать и параметры класса и параметры метода

- [code/tilir_masters/03_14_method_full_spec.cpp](code/tilir_masters/03_14_method_full_spec.cpp)
- Чтобы специализировать метод шаблонного класса, нужно не просто "съесть" параметр именно шаблонного метода, а также "съесть" параметр самого класса.
- Иначе компилятор подумает, что это частичная специализация функции, которая запрещена, потому что функция передается на неявный указатель на `this`.

```cpp
struct Data { template <typename T> T read() const; };

template <typename T> class DataReader {
    const T& source_;
public:
    template <typename R> R read();
};

template <>         // <=== съедаем параметр класса
template <>         // <=== съедаем параметр метода
string DataReader<Data>::read<string>() {
    return source_.template read<string>(); // <===
}
```

### Переходники типов - специализация метода класса по параметру шаблона класса

- https://accu.org/journals/overload/10/50/wigley_385/
- Паттерн — **переходник типов**, который позволяет решить проблему специализации метода класса по параметру шаблона класса.
- Это подход для реализации разных вариантов поведения в зависимости от типа, переданного в шаблонный параметр.
- Работает на механиземе перегрузки методов класса.

```cpp

template <typename T> struct Type2Type { // <=== Переходник типов
    typedef T OriginalType;
};

template <typename T1, typename T2>
struct A {
    void func() {
        internal_func(Type2Type<T1>()); // Использование переходника типов - работает на перегрузке.
    }
private:
    template <typename V> void internal_func(V) { cout << "all\n"; }

    void internal_func(Type2Type<int>) { cout << "int\n"; } // <=== Специализация метода класса
};

A<int, double> a;
A<float, double> b;

a.func(); // вызовется internal_func для int, благодаря разрешению перегрузки
b.func(); // вызовется internal_func для всех остальных типов
```

### Переходник типов для имитации частичной специализации функций

- Переходники `Type2Type` изначально были придуманы Александреску для ещё одной имитации частичной специализации функций.
- Красиво, хотя и накладывает обязательства. Критику и альтернативы можно найти в статье https://accu.org/journals/overload/10/50/wigley_385/. [TODO]
- Он решил задачу специализации метода класса по параметру шаблона класса (в качестве примера шаблонная функция-конструктор):

```cpp

// BEFORE: doen't compile
template <typename T, typename U> T* Create(const U& arg);
template <typename U> Widget* Create<Widget, U>(const U& arg); // not C++

// AFTER: works fine
template <typename T, typename U>
T* Create(const U& arg, Type2Type<T>);

template <typename U>
Widget* Create(const U& arg, Type2Type<Widget>);
```

## Вывод типов шаблонами классов

### Конструкторы классов могут использоваться для вывода типов (С++17)

- Классы сами по себе не могут выводить типы, но конструкторы классов в C++17 могут быть использованы для вывода типов.

```cpp
template <typename T>
struct container {
    container(T t);
    // и так далее
};

container c(7); // → container<int> c(7);
auto c = container(7); // → аналогично
auto c = new container(7); // → аналогично
```

### `Deduction Hints` - хинты вывода типов могут быть использованы для вывода типов конструкторами классов и агрегатами (С++17)

- Можно использовать `iterator_traits<Iter>::value_type`, а можно написать просто `Iter::value_type`. Однако `iterator_traits` предпочтительнее, потому что он умеет выводить типы для указателей, у которых нет вложенного типа `value_type`.

```cpp
template <class T>
struct container {
    template <class Iter>
    container(Iter beg, Iter end);
    // и так далее
};

// пользовательский хинт для вывода
template <class Iter>
container(Iter b, Iter e) -> container<typename iterator_traits<Iter>::value_type>;

vector<double> v;
auto d = container(v.begin(), v.end()); // → container<double>
```

## Разрешение имен (шаблоны классов)

### Двухфазное разрешение имен (тонкий пример)

- Что будет на экране?
- Аргумент `S x` в параметрах метода `call_foo` является независимым, поэтому он разрешается сразу и связывается с функцией `foo<S>(x)`, которая выводит `"S"`.
- Зависимый параметр `t`, который идет первым в аргументах, разрешается позже и уже будет распечатан как `"T"`.

```cpp
template<typename T> void foo (T) { std::cout << "T"; }

struct S { };

template<typename T> void call_foo (T t, S x) {
    foo (x); // x независимое имя, разрешается в foo<S>(x) <===
    foo (t); // t зависимое имя, разрешение откладывается  <===
}

void foo (S) { std::cout << "S"; }

int bar (S x) {
    call_foo (x, x); // здесь t разрешается в foo(S)
}
```

### Disambiguation (Разрешение неоднозначности): `.template`, `typename`

- Дизамбигуация (разрешение неоднозначности) требуется, когда есть зависимость от типа шаблона.
- Без явного указания `template` компилятор может попытаться интерпретировать `foo` как поле, а не как шаблонный метод, как это показано в данном случае.
- `typename` используется чтобы указать, что `T::subtype` является типом, а не статическим членом, который может участвовать в умножении.

```cpp
template<typename T> struct S {
    template<typename U> void foo(U *p) {}
};

template<typename T> int foo(const T& x) {
    typename T::subtype *y;                 // <=== typename
    S<T> s;
    s.template foo<T>(y);                   // <=== .template
}
```

### Отношение **общий**, **частный** в специализации шаблонных классов

- Задача на определение более частной или более общей специализации шаблонных классов **решается аналогично задаче перегрузки функций**.
- В данном случае **шаблонные классы трактуются как вызовы функций**. Путем сопоставления специализаций определяется, какая из них является более частной, а какая — более общей.

```cpp
template<int I, int J> class X<I, J, int> {};
template<int I> class X<I, I, int> {};

// Переписываем в функции с вымышленными аргументами
template<int I, int J> void f(X<I, J, int>);  // (1)
template<int I> void f(X<I, I, int>);        // (2)

// И мы получаем уже решённую задачу перегрузки для шаблонов функций:
f(X<I1, I2, int>); // не подходит для (2)
f(X<I1, I1, int>); // подходит для (1)
```

## --------------------- 04. Модули ---------------------

## One Definition Rule (ODR)

### Единица трансляции

- Единица трансляции была введена для того, чтобы сделать возможным существование статических и динамических библиотек.
- Как альтернатива, могла бы быть система, где все функции видны между всеми файлами без учета единиц трансляции.

```cpp
// myfile.cc
int bar();
int foo() { return bar() + 1; }
```

В данном случае мы говорим, что `foo` и `bar` используют внешнее связывание. Мы верим, что функция `bar()` где-то существует, и что мы правильно угадали её сигнатуру. Это создает риски ошибок и неприятностей, от которых мы можем попытаться застраховаться.

### Классы связывания

- **Виды связывания**:
  - Никакого связывания (no linkage) - переменная не может быть использована за пределами своего скоупа. Т.е. не видна линкеру.
  - Внешнее связывание (external linkage)
  - Внутреннее связывание (internal linkage)
  - Модульное связывание (module linkage)
- **Задавайте себе вопросы**:
  - Этот **definition** может быть **использован** в другом модуле?
  - Этот **declaration** может быть **прийти/вызыван** из другого модуля?

```cpp
extern int v0; // внешнее
static int v1; // внутреннее

int foo() { extern int y; } // внешнее
int bar() { static int z; } // никакого - не может быть вызван из другого места

template <typename T> int bar(T x); // внешнее
namespace { int buz(); } // внутреннее

struct T; // внешнее
template <typename T> struct U; // внешнее
struct S { static int x; }; // внешнее
```

### ODR(One Definition Rule)

- ODR - имя должно иметь одно определение в программе.
- ODR
  - No translation unit shall contain more than one definition of any variable, function, class type, enumeration type, template [...].
  - Every program shall contain exactly one definition of every **(1) non-inline** function or variable that is **(2) odr-used** in that program outside of a **(3) discarded statement**.
- После препроцессинга типы должны полексемно совпадать с их определениями.

```cpp
// header.h
#pragma once

// ok, т.к это исключение из ODR.
// Ключевое слово inline не влияет на связывание. Функция одна все все единицы трансляции.
// Как будто бы у нее есть небольшой свой модуль, который подлинкован ко всем и как будто там она есть.
// На самом деле это weak функция, и линковщик берет первую попавшуюся.
inline int foo(int n) { return n; }

static int bar(int n) { return n; } // ok, но multiple defs.
```

### (1) `non-inline` for ODR

- https://github.com/tilir/cpp-masters/blob/master/modules/fullspec.hpp
- `inline` - УСТАРЕВШЕЕ ЗНАЧЕНИЕ: это способ сказать компилятору, что функция должна быть вставлена в каждое место вызова.
- `inline` - НОВОЕ ЗНАЧЕНИЕ: означает исключение из ODR. Т.е. чтобы она была в header файле, но одна на все единицы трансляции.
  - Это свойство удобно использовать в **специализациях шаблонов**, которые специализированы **в header файле**.

### (2) `odr-used` for ODR

```cpp
struct S {
  static const int n = 5; // declaration
};

int x = S::n + 1; // n not ODR-used                         <=== определение не требуется

int foo(const int *x) { return *x; }

#if 0
const int S::n; // definition
#endif

int y = foo(&S::n) + 1; // n ODR-used [class.static.data]   <=== требуется определение
```

### (3) `discarded statement` for ODR

- "Не вычеркнуто с помощью `if constexpr`"
- Обратите внимание: `if constexpr` влияет на инстанцирование и на ODR

```cpp
extern int x;

int foo() {
    if constexpr(false) { return x; }   // <=== if constexpr(false) - discarded statement - не требует определения
    else return 0;
}

template <int N> int bar() {
    if constexpr(false) { return x; }   // <===
    else return 0;
}
```

### Предкомпилированные header файлы (первая попытка ускорить компиляцию)

- Откомпилированный заголовочный файл содержит AST (Abstract Syntax Tree) вместо текста.
- Компиляция header файла создает предкомпилированный файл с расширением `.gch`.

```cpp
// hello-afx.h
#pragma once
#include <iostream>
#include <string>
#include <vector>
// и так далее

// hello-afx.cpp
#include "hello-afx.h"

// > g++ -O2 stdafx.h                               # создаст stdafx.h.pch
// > g++ -O2 hello-afx.cc # найдёт stdafx.h.pch     # использует stdafx.h.pch вместо hello-afx.h
```

### Модули (C++20) - идеальные предкомпилированные header файлы

- https://github.com/tilir/cpp-masters/tree/master/modules/simplest
- https://youtu.be/Dsfccho1QX0?t=1416

- Минусы предкомпилированных header файлов:
  - Мы хотим управлять видимостью и хотим управлять linkage.
  - В предкомпилированных header все символы видны всем, а не только тем, кто их импортировал.

- Модули - это идеальные предкомпилированные header файлы с
  - `module linkage` связыванием.
  - Регулировкой видимости.

- `Модульное связывание` - доступно из всех единиц трансляций входящих в модуль.
  - В других единицах трансляции это будет другое имя.

**Пишем модуль**

```cpp
export module first_module;         // Модуль может содержать несколько единиц трансляции. Только одна из них может быть экспортная.

namespace hello {

int foo(int x) { return x; }        // Модульное связывание. Деталь реализации.

export int e = 42;                  // Внешнее связывание. Экспортируется из модуля. Нет ODR violation.

export int bar() { return foo(e); } // Внешнее связывание, но объявление ровно одно на все места, где влючен этот модуль. Похоже на inline. Нет ODR violation.

} // namespace hello
```

**Используем модуль**

```cpp
// main.cpp

#include <iostream>

import first_module;

int main() {
  std::cout << "foo: " << hello::foo() << std::endl;    // Error because foo is not visible
  std::cout << "bar: " << hello::bar() << std::endl;    // OK: 42
  std::cout << "e: " << hello::e << std::endl;          // OK: 42
}
```

`
**Сборка**

```bash
# компиляция модуля
clang++ --std=c++20 -fmodules --stdlib=libc++ --precompile first_module.cppm -o first_module.pcm

# компиляция main c использованием модуля
clang++ --std=c++20 -fmodules --stdlib=libc++ -fmodule-file=first_module.pcm first_module.pcm main.cc
```

### Импортируем модуль в модуль

**Экспорт без транзитивности**

```cpp
export module first_extended;               // Экспортируем новый модуль
import first_module;                        // Импортируем первый модуль, но не видим его содержимое вне нового модуля(не транзитивно).
export int bar() { return hello::bar(); }   // Используем функцию из первого модуля.
```

**Экспорт с транзитивностью**

```cpp
export module first_extended;         // Экспортируем новый модуль
export import first_module;           // Импортируем первый модуль и видим его содержимое вне нового модуля(транзитивно).
export int buz() { return bar(); }    // Используем функцию из первого модуля.
```

**importable header**

- `import <iostream>;` - в данном случае это дирректива препроцессора. Не путать ее с `import module;`.
  - Эта команда берет header.
  - Предкомпилирует его.
  - Делает из него модуль.
  - Импортирует его.
  - Также импортируются макросы! Обычный импорт не импортирует макросы.
- Не любой header может быть importable. Это зависит от реализации стандартной библиотеки.

```cpp
export module helloworld;
import <iostream>;                                                  // Importable header
export void hello() { std::cout << "Hello, World!" << std::endl; }
```

**Циклические зависимости диагностируются на этапе компиляции**

```cpp
export module M1; // file: M1.cppm
import M2;

export module M2; // file: M2.cppm
import M3;

export module M3; // file: M3.cppm
import M1;                          // <=== Error: cyclic dependency
```

```cpp
export module M1; // file: M1.cppm
export int foo() { return 42; }

export module M2; // file: M2.cppm
export int foo() { return 42; }     // <=== Error: multiple definitions
```

### Что нельзя экспортировать из модуля

```cpp
// Имена с внутренним связыванием.
export static int x; // ошибка
namespace { export int x; } // ошибка

// Имена со связыванием на уровне модуля.
struct S; // тут S неполный тип, module linkage
export struct S; // ошибка (ok, если убрать строчку выше)

// Нечто, вообще не являющееся объявлением, вводящим имя.
export using namespace N; // ошибка
```

### Глобальный фрагмент модуля, в который можно сделать `include`

```cpp
module;                 // Глобальный фрагмент модуля
#include <iostream>;    // Тут можно делать только диррективы препроцессора: include, define...

export module hello;    // Экспорт модуля
import <string>;        // Импорт должен быть до всех decls

// Содержимое модуля (exports и прочее, также говорят "perview")

```

## --------------------- 05. SFINAE ---------------------

## SFINAE (Substitution Failure Is Not An Error)

### Можно создавать шаблонные переменные

```cpp
template<typename T, typename U> struct is_same : false_type {};
template<typename T> struct is_same<T, T> : true_type {};
template<typename T, typename U>
using is_same_t = typename is_same<T, U>::type;

// Так лучше не делать, потому что эта
// переменная будет находится в глобальной памяти.
template<typename T, typename U>
bool is_same_v = is_same<T, U>::value; // не is_same_t<....>::value!    // <=== шаблонная переменная в шлобальной памяти

assert (is_same<int, int>::value && is_same<char, int>::value);
assert (is_same_v<int, int> && !is_same_v<char, int>);

// Лучше использовать constexpr переменные в шаблонах
template<typename T, typename U>
constexpr bool is_same_v2 = is_same<T, U>::value;                       // <=== шаблонная переменная constexpr

```

### SFNIAE unwrapping

```cpp
using is_same_t = typename is_same<T, U>::type;

template <typename T> struct not_ : false_type {};
template <> struct not_<false_type> : true_type {};
template <typename T> using not_t = typename not_<T>::type;         // <=== unwrapping alias

assert(and_v<is_same  <int, int>, not_ <is_same  <char, int>>>);    // Error: потому что нет unwarapping
assert(and_v<is_same_t<int, int>, not_t<is_same_t<char, int>>>);    // OK
```

### Использование `void_t`, чтобы спросить, если у типа определенный метод (интерфейс)

```cpp
template <typename, typename = void>
struct has_typedef_foobar : false_type { };

template <typename T>
struct has_typedef_foobar<T, void_t<typename T::foobar>> : true_type { };
```

### `void_t` — это не шаблон, это алиас. Алиасы имеют некоторые особенности

- Полная и частичная специализация шаблонов алиасов невозможна.

```cpp
template <typename T> using MyType = std::vector<T>;
template <> using MyType<int> = int; // ошибка
```

- Алиасы шаблонов не выводятся выводом типов:

```cpp
template <class T> using Vec = std::vector<T>;

Vec<int> v; // std::vector<int, std::allocator<int>> v;

template <template <typename> typename TT> void f(TT<int>);

f(v); // ошибка вывода
```

### ENABLE_IF - условная конструкция для типов

- Получившаяся триада `enable_if` является одной из самых полезных идиом в практическом SFINAE.
- Она используется, чтобы выкидывать (sfinae-out) инстанциации шаблонов.
- Для тренировки дома можно попробовать
  - найти n-ное простое число на этапе компиляции, используя шаблоны в C++ [TODO].
  - Факториал на этапе компиляции [TODO].
  - Числа Фибоначчи на этапе компиляции [TODO].
  - Целочисленный квадратный корень на этапе компиляции [TODO].

```cpp
template <bool B, typename T = void>
struct enable_if { using type = T; };

template <typename T = void>
struct enable_if<false, T> {};

template <bool B, typename T = void>
using enable_if_t = typename enable_if<B, T>::type;
```

## --------------------- 06. Constexpr ---------------------

### `if constexpr` - выкидывает ветки ШАБЛОННЫХ инстанцирований

- https://godbolt.org/z/xKz77dEeY
- `if constexpr` - выкидывает ветки шаблонных инстанцирований
  - весь код во всех ветках проходит через первую фазу инстанцирования шаблонов
  - Но на второй фазе компилятор выкидывает `if constexpr (false)` ветки.

```cpp
// (1) template case: constexpr works

template <typename T>
void bar(T value) {
  if constexpr (std::is_pointer_v<T>)
    std::cout << "Ptr to " << *value << std::endl; // Error
  else
    std::cout << "Ref to " << value << std::endl;
}

template void bar<int>(int); // instantiate here!
template void bar<int*>(int *); // instantiate here!

// (2) non-template case: constexpr fails

void foo() {
  auto value = 100; // deduce int
  if constexpr (std::is_pointer_v<decltype(value)>)
    std::cout << "Ptr to " << *value << std::endl; // Error
  else
    std::cout << "Ref to " << value << std::endl;
}
```

### `constexpr` функции времени компиляции

- Написать целочисленный логарифм времени компиляции (https://youtu.be/jyYys1UcHkM?t=2868).

### `consteval` (C++20)

- [code/tilir_masters/06_10_challange_math_trit_via_consteval.cpp](code/tilir_masters/06_10_challange_math_trit_via_consteval.cpp)
- [code/tilir_masters/06_12_challange_math_array_size.cpp](code/tilir_masters/06_12_challange_math_array_size.cpp)
- [code/tilir_masters/06_14_challange_bitmask_logic_or.cpp](code/tilir_masters/06_14_challange_bitmask_logic_or.cpp)
- `consteval` - это `constexpr`, который гарантирует, что функция будет вызвана во время компиляции.

```cpp

// https://youtu.be/jyYys1UcHkM?t=4444
// Тритами называются цифры сбалансированной системы счисления
// по основанию 3. Т.е. {-1, 0, 1}. Обозначим -1 как j.
// Написать функцию вычисления в compile-time.
// [TODO] написать также для вещественных чисел: 11j0.jj = 32 + 5/9
template <typename T = int>
consteval T ct_trit(const char* str)
{
    T result = 0;

    for (size_t i = 0; str[i] != '\0'; ++i)
    {
        char ch = str[i];

        switch (ch)
        {
        case '0': result *= 3; break;
        case '1': result = result * 3 + 1; break;
        case 'j': result = result * 3 - 1; break;
        default: throw "Only ['0','1','j'] symbols may be used";
        }
    }

    return result;
}

// https://youtu.be/jyYys1UcHkM?t=4630
// Написать вычисление длины массива времени компиляции
template <typename T, size_t SZ>
consteval size_t arraySize(const T(&)[SZ])
{
    return SZ;
}

// Написать класс для конкатенации битовых масок.
// Сделать это в compile-time, чтобы такое можно было использовать в switch.
enum class bitmask
{
    b0 = 0x1,
    b1 = 0x2,
    b2 = 0x4
};

consteval bitmask operator|(bitmask v0, bitmask v1)
{
    return static_cast<bitmask>(int(v0) | int(v1));
}

```

### `constinit` (С++20)

- [code/tilir_masters/06_01_constinit.cpp](code/tilir_masters/06_01_constinit.cpp)
- `constinit` - не просто форсит `constexpr`, но гарантирует статическую констунтную инициализацию, что не возможно для объектов на стеке.
- Невозможно создать локальную `constinit` переменную.

### `if consteval` (C++23)

- `if consteval` - помогает узнать внутри функции, находимся мы на этапе компиляции или на этапе выполнения.

```cpp
constexpr size_t int_log (size_t N)
{
    if consteval                    // <=== if consteval
    {
        return int_log_ce(N);       // Выполняется на этапе компиляции
    }
    else
    {
        return __builtin_ctz(N);    // Выполняется на этапе выполнения
    }
}
```

### Core constant expressions

- [code/tilir_masters/06_16_core_constant_expr.cpp](code/tilir_masters/06_16_core_constant_expr.cpp)
- Такое ощущение, что `constexpr` метод класса может быть `static`.
- Все что использует этот метод, тоже должно быть `constexpr`.

```cpp
struct S
{
    int n_;
    S(int n) : n_(n) {}     // <===  non-constexpr ctor!
    constexpr int get() { return 42; }
};

TEST(cexpr, cce)
{
    S s{2};
    constexpr int k =
        s.get();            // <=== Core Constant Expression
    EXPECT_EQ(k, 42);
}
```
