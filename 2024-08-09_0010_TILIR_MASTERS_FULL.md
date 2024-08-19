- [01. Strings](#01-strings)
  - [Стандартные преобразования: lvalue to rvalue, array to pointer, function to function pointer](#стандартные-преобразования-lvalue-to-rvalue-array-to-pointer-function-to-function-pointer)
  - [Побочные эффекты и asm](#побочные-эффекты-и-asm)
  - [Проблема `C-строк`](#проблема-c-строк)
  - [`std::string_view` (C++17)](#stdstring_view-c17)
  - [Идиома COW (Copy-On-Write) для `std::string` провалилась](#идиома-cow-copy-on-write-для-stdstring-провалилась)
  - [SSO (Small String Optimization) for `std::string`](#sso-small-string-optimization-for-stdstring)
- [02. Шаблоны функций](#02-шаблоны-функций)
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
- [03.1 Шаблоны классов](#031-шаблоны-классов)
  - [ODR (One Definition Rule) для классов и функций работает по разному](#odr-one-definition-rule-для-классов-и-функций-работает-по-разному)
  - [Частичная специализация шаблонов (работает только для классов)](#частичная-специализация-шаблонов-работает-только-для-классов)
  - [Частичная специализация не всегда должна иметь меньше или равное количество шаблонов-параметров](#частичная-специализация-не-всегда-должна-иметь-меньше-или-равное-количество-шаблонов-параметров)
  - [Трюк Саттера для создания частичной специализации функции через класс](#трюк-саттера-для-создания-частичной-специализации-функции-через-класс)
  - [Специализация классов только лишь похожа на наследование - она нарушает LSP (Liskov Substitution Principle)](#специализация-классов-только-лишь-похожа-на-наследование---она-нарушает-lsp-liskov-substitution-principle)
- [03.2 Шаблоны классов - Специализация методов классов](#032-шаблоны-классов---специализация-методов-классов)
  - [`.template` используется для разрешения неоднозначности, если мы хотим вызвать шаблонный метод](#template-используется-для-разрешения-неоднозначности-если-мы-хотим-вызвать-шаблонный-метод)
  - [Для специализации шаблонного метода шаблонного класса нужно съедать и параметры класса и параметры метода](#для-специализации-шаблонного-метода-шаблонного-класса-нужно-съедать-и-параметры-класса-и-параметры-метода)
  - [Переходники типов - специализация метода класса по параметру шаблона класса](#переходники-типов---специализация-метода-класса-по-параметру-шаблона-класса)
  - [Переходник типов для имитации частичной специализации функций](#переходник-типов-для-имитации-частичной-специализации-функций)
- [03.3 Шаблоны классов - Вывод типов шаблонами классов](#033-шаблоны-классов---вывод-типов-шаблонами-классов)
  - [Конструкторы классов могут использоваться для вывода типов (С++17)](#конструкторы-классов-могут-использоваться-для-вывода-типов-с17)
  - [`Deduction Hints` - хинты вывода типов могут быть использованы для вывода типов конструкторами классов и агрегатами (С++17)](#deduction-hints---хинты-вывода-типов-могут-быть-использованы-для-вывода-типов-конструкторами-классов-и-агрегатами-с17)
- [03.4 Шаблоны классов - Разрешение имен](#034-шаблоны-классов---разрешение-имен)
  - [Двухфазное разрешение имен (тонкий пример)](#двухфазное-разрешение-имен-тонкий-пример)
  - [Disambiguation (Разрешение неоднозначности): `.template`, `typename`](#disambiguation-разрешение-неоднозначности-template-typename)
  - [Отношение **общий**, **частный** в специализации шаблонных классов](#отношение-общий-частный-в-специализации-шаблонных-классов)
- [04.1 Модули - One Definition Rule (ODR)](#041-модули---one-definition-rule-odr)
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
- [05. SFINAE (Substitution Failure Is Not An Error)](#05-sfinae-substitution-failure-is-not-an-error)
  - [Можно создавать шаблонные переменные](#можно-создавать-шаблонные-переменные)
  - [SFNIAE unwrapping](#sfniae-unwrapping)
  - [Использование `void_t`, чтобы спросить, если у типа определенный метод (интерфейс)](#использование-void_t-чтобы-спросить-если-у-типа-определенный-метод-интерфейс)
  - [`void_t` — это не шаблон, это алиас. Алиасы имеют некоторые особенности](#void_t--это-не-шаблон-это-алиас-алиасы-имеют-некоторые-особенности)
  - [ENABLE\_IF - условная конструкция для типов](#enable_if---условная-конструкция-для-типов)
- [06. Constexpr](#06-constexpr)
  - [`if constexpr` - выкидывает ветки ШАБЛОННЫХ инстанцирований](#if-constexpr---выкидывает-ветки-шаблонных-инстанцирований)
  - [`constexpr` функции времени компиляции](#constexpr-функции-времени-компиляции)
  - [`consteval` (C++20)](#consteval-c20)
  - [`constinit` (С++20)](#constinit-с20)
  - [`if consteval` (C++23)](#if-consteval-c23)
  - [Core constant expressions](#core-constant-expressions)
  - [`constexpr` не сохраняется через передачу по аргументам](#constexpr-не-сохраняется-через-передачу-по-аргументам)
  - [В `constexpr-функциях` на этапе компиляции запрещено UB.](#в-constexpr-функциях-на-этапе-компиляции-запрещено-ub)
  - [`constexpr-evaluation` и контейнер, который работает на этапе компиляции (С++14)](#constexpr-evaluation-и-контейнер-который-работает-на-этапе-компиляции-с14)
  - [Виртуальные constexpr функции (C++20)](#виртуальные-constexpr-функции-c20)
  - [`constexpr new`](#constexpr-new)
  - [`Вариабельный суффикс` - пользовательские литералы времени компиляции через вариабельные шаблоны](#вариабельный-суффикс---пользовательские-литералы-времени-компиляции-через-вариабельные-шаблоны)
  - [`Cтроковые литералы` - как писать пользовательские литералы времени компиляции для строк](#cтроковые-литералы---как-писать-пользовательские-литералы-времени-компиляции-для-строк)
  - [Литералы `физических величин` и автоматический контроль размерности](#литералы-физических-величин-и-автоматический-контроль-размерности)
  - [`boost::hana` - Представление типов значениями](#boosthana---представление-типов-значениями)
  - [Перенос процесса `инстанцирования` на процесс `Constexpr Evaluation` (быстрее и мы хотим этого)](#перенос-процесса-инстанцирования-на-процесс-constexpr-evaluation-быстрее-и-мы-хотим-этого)
- [07. Concepts](#07-concepts)
  - [Неявный интерфейс](#неявный-интерфейс)
  - [Используем SFINAE, чтобы сделать более явным интерфейс (костыль)](#используем-sfinae-чтобы-сделать-более-явным-интерфейс-костыль)
  - [Используем `if constexpr` и `static_assert` для явного интерфейса](#используем-if-constexpr-и-static_assert-для-явного-интерфейса)
  - [Используем `Constraints(ограничения)` для явного интерфейса (`requires`)](#используем-constraintsограничения-для-явного-интерфейса-requires)
  - [`Concepts` - ограничения с отношениями частное-общее](#concepts---ограничения-с-отношениями-частное-общее)
  - [Что такое `Concept`?](#что-такое-concept)
  - [Карирование аргументов](#карирование-аргументов)
  - [Концепты определяют над собой частичный порядок (частное-общее)](#концепты-определяют-над-собой-частичный-порядок-частное-общее)
- [08. Type Inference (Вывод типов)](#08-type-inference-вывод-типов)
  - [Категории выражений](#категории-выражений)
  - [`rvalue` всегда связывается с `modifiable rvalue reference` (`T&&` - `not const T&&`)](#rvalue-всегда-связывается-с-modifiable-rvalue-reference-t---not-const-t)
  - [`RVO` (Return Value Optimization) and `NRVO` (Named RVO)](#rvo-return-value-optimization-and-nrvo-named-rvo)
  - [Надо различать вызван ли `decltype` от `имени` или от `выражения`](#надо-различать-вызван-ли-decltype-от-имени-или-от-выражения)
  - [`decltype(auto)` ведет себя как `decltype`, но при этом выводится из всей правой части](#decltypeauto-ведет-себя-как-decltype-но-при-этом-выводится-из-всей-правой-части)
  - [`decltype(auto)` разбор примера](#decltypeauto-разбор-примера)
  - [`auto` можно уточнять концептами](#auto-можно-уточнять-концептами)
  - [Правила написания правильных ограничений для шаблонов (используйте только позитивные ограничения)](#правила-написания-правильных-ограничений-для-шаблонов-используйте-только-позитивные-ограничения)
- [09. Variadic Templates](#09-variadic-templates)
  - [C-style `...`](#c-style-)
  - [C++ style `...`](#c-style--1)
  - [`Variadic Templates` - несколько простых примеров](#variadic-templates---несколько-простых-примеров)
  - [`Variadic Templates` - более сложные примеры](#variadic-templates---более-сложные-примеры)
  - [Документация по паттернам раскрытия](#документация-по-паттернам-раскрытия)
  - [Экзотические свертки](#экзотические-свертки)
  - [Светрки с пустыми пачками тоже работают](#светрки-с-пустыми-пачками-тоже-работают)
  - [`std::conjunction_v` - проверка всех типов на истинность](#stdconjunction_v---проверка-всех-типов-на-истинность)
  - [Вариабельные концепты и каррирование](#вариабельные-концепты-и-каррирование)
  - [Свертки очень важны для концептов, так как у нас нет рекурсии и выхода (нет откусывания пачки)](#свертки-очень-важны-для-концептов-так-как-у-нас-нет-рекурсии-и-выхода-нет-откусывания-пачки)
  - [Пачка параметров обычно должна идти последним аргументом, т.к. из за жадности она заберет все последующие аргументы](#пачка-параметров-обычно-должна-идти-последним-аргументом-тк-из-за-жадности-она-заберет-все-последующие-аргументы)
  - [Пример с `auto` для вывода указателя на поле класса](#пример-с-auto-для-вывода-указателя-на-поле-класса)
- [10. Lambda-выражения](#10-lambda-выражения)
  - [Синтаксис `->` для указания типа возвращаемого значения (C++11)](#синтаксис---для-указания-типа-возвращаемого-значения-c11)
  - [Что такое `λ-выражение` и `closure` без захвата](#что-такое-λ-выражение-и-closure-без-захвата)
  - [`std::invoke` и callable объекты](#stdinvoke-и-callable-объекты)
  - [`std::invoke` и указатель на поле класса](#stdinvoke-и-указатель-на-поле-класса)
  - [Positive Lambda Hack](#positive-lambda-hack)
  - [Generic Lambda - это лямбда-функция с шаблонным оператором приведения](#generic-lambda---это-лямбда-функция-с-шаблонным-оператором-приведения)
  - [`decltype([](auto x) { return 2 * x; })` - лучший способ запомнить lambda тип (С++20)](#decltypeauto-x--return-2--x----лучший-способ-запомнить-lambda-тип-с20)
  - [Явные шаблонные аргументы (С++20)](#явные-шаблонные-аргументы-с20)
  - [Лямбда-функции c захватом](#лямбда-функции-c-захватом)
  - [Захват c явным переименованием](#захват-c-явным-переименованием)
  - [Илучшаем свой идеальный проброс](#илучшаем-свой-идеальный-проброс)
  - [Захват с вариабельными пачками (C++20)](#захват-с-вариабельными-пачками-c20)
  - [Карирование функции - это частичная подстановка ее аргументов](#карирование-функции---это-частичная-подстановка-ее-аргументов)
  - [Захватывается только локальный нестатический контекст](#захватывается-только-локальный-нестатический-контекст)
  - [Четыре способа создать `std::tuple`](#четыре-способа-создать-stdtuple)
  - [`std::forward_as_tuple` для решения проблемы форвардинга пачки агрументов в лямбда захват](#stdforward_as_tuple-для-решения-проблемы-форвардинга-пачки-агрументов-в-лямбда-захват)
  - [`std::apply` - для применения функции к каждому агрументу](#stdapply---для-применения-функции-к-каждому-агрументу)
  - [`std::any` - стирает типы](#stdany---стирает-типы)
  - [`std::variant` - альтернатива `std::any`, которая хранит только один из заданных типов](#stdvariant---альтернатива-stdany-которая-хранит-только-один-из-заданных-типов)

## 01. Strings

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

- Написать Lazy строку за 15 минут [TODO] [PRACTICE]
  - Проблемы, например, с многопоточностью, потому что RefCount не защищен.
  - Безопасность относительно исключений.
  - Семантика перемещения.

```cpp
lass stringbuf {
    char *data;
    size_t size;
    size_t capacity;
    int refcount;
    // etc...
};

class string {
    stringbuf *buf;
    // etc...
};
```

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

- Напишите для `basic_string` сравнение (`operator==`) [TODO] [PRACTICE]
  - Сделаете ли вы этот оператор методом класса или свободной функцией?
  - Как должны сравниваться строки с одинаковым `CharT`, но разными `Traits`?
  - А если у них одинаковые `CharT` и `Traits`, но разные аллокаторы?

```cpp
template <typename CharT,
          typename Traits = std::char_traits<CharT>,
          typename Allocator = std::allocator<CharT>>
class basic_string { ... };
```

## 02. Шаблоны функций

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

## 03.1 Шаблоны классов

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

## 03.2 Шаблоны классов - Специализация методов классов

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

## 03.3 Шаблоны классов - Вывод типов шаблонами классов

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

## 03.4 Шаблоны классов - Разрешение имен

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

## 04.1 Модули - One Definition Rule (ODR)

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

## 05. SFINAE (Substitution Failure Is Not An Error)

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

## 06. Constexpr

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

### `constexpr` не сохраняется через передачу по аргументам

- Компилятор ориентируется на синтаксис.
- `constexpr` не сохраняется через передачу по аргументам. Вместо этого можно было бы передавать как шаблонный параметр.
- В примере ниже компилятор выполняет синтаксический анализ, и вызов `PRED(TRUE)` не является `constexpr-выражением`, поэтому компиляторы возвращают здесь ошибки.

```cpp
consteval bool negate(bool x) { return !x; }

template <typename Predicate>
constexpr int f(Predicate pred) {
    if constexpr (pred(true))       // <=== не является constexpr - ошибка компиляции
        return 1;
    return 0;
}

constexpr int x = f(negate);
```

### В `constexpr-функциях` на этапе компиляции запрещено UB.

- Любое выражение, которое могло бы привести к UB в runtime, в compile-time вызовет ошибку.
- Поэтому `constexpr`-функции можно использовать как UB-санитайзеры.

```cpp
template <typename FwdIt, typename Value>
constexpr FwdIt static_find(FwdIt it, FwdIt fin, Value v) {
    while ((v != *it) && (it != fin)) ++it;
    return it;
}

int a[] = {1};
static_find(a, a + 1, 4); // array subscript value '1' is
                          // outside the bounds of array
```

### `constexpr-evaluation` и контейнер, который работает на этапе компиляции (С++14)

- Написать собственный контейнер, который будет работать во время компиляции, чтобы набить руку [TODO] [PRACTICE].
- Это работает благодаря тому, что в C++14 добавился процесс `constexpr-evaluation` к таким процессам, как инстанцирование вывод типов и подобное.

```cpp
template <typename T, size_t N>
class array_result {
    constexpr static size_t size_ = N;
    T data_[N] {};
public:
    template <typename ... Ts>
    constexpr array_result(Ts ... ints) : data_{ints...} {}

    constexpr size_t size() const { return N; }
    constexpr T& operator[](size_t n) { return data_[n]; }

    using iterator = const T*;
    constexpr iterator begin() const { return data_; }
    constexpr iterator end() const { return data_ + N; }
};
```

### Виртуальные constexpr функции (C++20)

- На самом деле, constexpr-виртуальные методы не создают виртуальную таблицу.
- Происходит иллюзия Type Erasure. Компилятор помнит все типы, и вызов по базовому указателю не будет через vtable.
- Таким образом, введённые в C++20 virtual constexpr функции — это псевдо-стирание типов.

```cpp
struct Base { // Нет constexpr конструктора
  virtual constexpr int data() const { return 1; }
};

struct Derived : Base {
  constexpr int data() const override { return 2; }
};

constexpr int foo() {
  const Base b;
  const Derived d;
  const Base *bases[] = {&b, &d};
  return bases[0]->data(); // обычное использование внутри функции
}
```

```cpp
  const Base *bases[] = {&b, &d};

  // Если эта функция действительно выполняется во время
  // компиляции, компилятор отлично запомнит типы.
  for (auto pb : bases)
    sum += pb->data();
```

### `constexpr new`

- `[expr.const] [E не является constexpr, если его частью является] a new-expression, unless the selected allocation function is a replaceable global allocation function and the allocated storage is deallocated within the evaluation of E.`

- То есть следующее будет работать и работает:
- `Constexpr Evaluation` позволяет писать new в своих функциях, но запрещает эту память отдавать наружу. Нужно обязательно вызывать `delete`, иначе будут ошибки при компиляции.

```cpp
constexpr int test() {
    int *p = new int(2); // почему бы не std::vector?
    int k = *p;
    delete p;
    return k;
}
```

### `Вариабельный суффикс` - пользовательские литералы времени компиляции через вариабельные шаблоны

- Допустим, хочется переопределить суффикс `_binary` для бинарных констант.
- Решение: вариабельный суффикс.
- `binparser` - отбрасывает элементы из пачки по одному.

```cpp
template<char... Chars>
constexpr unsigned long long operator "" _binary() {
    return binparser(0ull, Chars...);
}
```

### `Cтроковые литералы` - как писать пользовательские литералы времени компиляции для строк

- Попытка применить: `10j01_tr1t` заставляет компилятор рассматривать `j01_tr1t` как суффикс.
- Более общий подход: строковые литералы.
- Нужно использовать кавычки и по-честному принимать указатель на `const char` и размер.
- Дополнить существующий пример литераля времени компиляции для тритов [CODE](code/tilir_masters/06_10_challange_math_trit_via_consteval.cpp) [TODO] [PRACTICE].

```cpp
constexpr long long
operator "" _tr1t(char const *s, size_t len) { // <===
    return ct_tr1t<long long>(s);
}

constexpr long long n = "10j01"_tr1t;
```

### Литералы `физических величин` и автоматический контроль размерности

- Цель: работа с физическими величинами с контролем размерности на этапе компиляции.
- По аналогии с физическими величинами можно использовать эту технику в вашем игровом движке.  [TODO] [PRACTICE]
  - чтобы делать переводы систем координат в Compile Time в нужное пространство координат.
  - Я не уверен, что это получится, но кажется, что получится.

```cpp
Speed sp1 = 100_m / 9.8_s;     // ok
Speed sp2 = 100_m / 9.8_s2;    // ошибка (м/с² это ускорение)
Speed sp3 = 100 / 9.8_s;       // ошибка (1/с это частота)
Acceleration acc = sp1 / 0.5_s; // ok

// Идея для решения: единица измерения как `enum`.
template<int M, int K, int S> struct Unit {         // <===
    enum { m=M, kg=K, s=S };
};
```

### `boost::hana` - Представление типов значениями

- Благодаря `constexpr` функциям в языке мы можем работать со значениями.
- Эти идеи легли в основу `boost::hana`.
- Представлен пример использования мощной библиотеки `boost::hana` для преобразования типов с использованием лямбда-функции на этапе компиляции. [TODO] [PRACTICE]

```cpp
template <typename T> struct type {};

template <typename T>
constexpr type<T*> add_pointer(type<T>) { return {}; }

auto types = hana::tuple_t<int, char, float, void>;
auto pointers = hana::transform(types, [](auto t) {     // <===
    return add_pointer(t);
});
```

### Перенос процесса `инстанцирования` на процесс `Constexpr Evaluation` (быстрее и мы хотим этого)

- Аналог `mpl::find` из `boost::mpl` на `constexpr` функциях.
- Основная идея этого слайда заключается в переносе процесса инстанцирования на процесс `Constexpr Evaluation`, поскольку он, вероятно, работает быстрее, чем традиционные методы инстанцирования шаблонов.

```cpp
template <int N> struct ct_ints {
    std::array<int, N> arr_;

    template <int... Is>
    constexpr ct_ints(std::integer_sequence<int, Is...>) : arr_{Is...} {}

    constexpr int find(int tag) const {
        for(int i = 0; i < N; ++i)
            if (arr_[i] == tag)
                return i;
        return N + 1;
    }
};
```

## 07. Concepts

### Неявный интерфейс

```cpp
// (1). В этом примере мы не видим явный интерфейс, который требуется от `range`.
template<typename R, typename T>
bool contains (R const& range, T const& value) {
    for (auto const& x : range)
      if (x == value)
        return true;
    return false;
}
```

### Используем SFINAE, чтобы сделать более явным интерфейс (костыль)

- Используем SFINAE, чтобы сделать более явным интерфейс (костыль). Способы:
  - (1) Ввести шаблонный параметр.
  - (2) Испортить возвращаемый тип (усложняется перегрузка, потому что по возвращаемому значению перегружать нельзя).
  - (3) Испортить один из параметров функции (получаем испорченный вывод типов).
- ПРОБЛЕМА: мы объюзим механиз SFINAE и можем его сломать явно указав все параметры шаблона.

```cpp
template <typename T, typename U, typename = void>
struct is_equality_comparable : std::false_type {};
template <typename T, typename U>
struct is_equality_comparable <T, U,
  std::void_t<decltype(std::declval<T>() == std::declval<U>())>
>: std::true_type {};

template <typename T, typename U,
          typename = std::enable_if_t <is_equality_comparable<T, U>::value>> // <=== SFINAE - вводим дополнительный шаблонный параметр
bool check_eq (T &&lhs, U &&rhs) {
  return (lhs == rhs);
}

check_eq<int, int,
    void                // <=== (2) ПРОБЛЕМА: мы объюзим механиз SFINAE и можем его сломать таким образом.
    >(1, "2")`.
```

### Используем `if constexpr` и `static_assert` для явного интерфейса

- Используем `if constexpr` и `static_assert` для явного интерфейса.
- Проблема в том, что приходится лезть внутрь функции и смотреть на код. Наружение OCP принципа.

```cpp
template <typename T, typename U>
bool check_eq (T &&lhs, U &&rhs) {
  if constexpr (!is_equality_comparable<T, U>::value) {     // <=== Используем if constexpr для выбрасывания плохой ветки.
    static_assert(0 && "equality comparable expected");     // <=== Используем static_assert для хорошей ошибки.
    return false;
  }
  else {
    return (lhs == rhs);
  }
}
```

### Используем `Constraints(ограничения)` для явного интерфейса (`requires`)

- https://godbolt.org/z/MWMzxjcoK

```cpp
template <typename T, typename U>
requires is_equality_comparable<T, U>::value    // <=== Используем requires для явного интерфейса
bool check_eq (T &&lhs, U &&rhs) {
  return (lhs == rhs);
}
```

- Ограничения (constraints) можно комбинировать
- https://godbolt.org/z/4T66PjEcs

```cpp
template <typename Iter>
  requires is_forward_iterator<Iter>::value &&                      // <=== Комбинирование ограничений
           is_totally_ordered<typename Iter::value_type>::value
Iter my_min_element(Iter first, Iter last) {
  Iter min = first;
  while (first != last) {
    if (*first < *min)
      min = first;
    ++first;
  }
  return min;
}
```

- `requires` - Это хук разрешения имен. Поэтому работает и такой код
- https://godbolt.org/z/GPs6jzKKj
- [over.dcl] two function declarations of the same name refer to the same function if they are in the same scope and have equivalent parameter declarations and equivalent **trailing requires-clauses**, if any.
- По простому функции считаются разными. Они счтаются разными полексемно (лексемы внутри `requires`)
- `requires` не входит в манглирование.

```cpp

template <typename T> requires (sizeof(T) > 4) // OK
int foo (T x) { return 1; }
template <typename T> requires (sizeof(T) <= 4) // OK
int foo (T x) { return 2; }

// В отличие от SFINAE:
template <typename T, typename = std::enable_if_t<(sizeof(T) > 4)>> // FAIL
int foo (T x) { return 1; }
template <typename T, typename = std::enable_if_t<(sizeof(T) <= 4)>> // FAIL
int foo (T x) { return 2; }

```

- Проблема с `requires` - это отсутвие отношения частное-общее.

### `Concepts` - ограничения с отношениями частное-общее

- `requires requires` - это `requires-clause + requires-expression`.
  - `requires-clause` - условие над функцией.
  - `requires-expression` - выражение, которое мы вычисляем на этапе компиляции. Это `constexpr` предикат над SFINAE характеристиками.

- https://godbolt.org/z/fjPMK4zY7

```cpp
template <typename T, typename U>
  requires requires(T t, U u)
                                { t == u; }     // <=== не вычисляется, а только оценивается(проверяется на валидность).
bool check_eq (T &&lhs, U &&rhs) {
  return (lhs == rhs);
}
```

- Сравните `requires` и `requires requires`:
- https://godbolt.org/z/edY544jEb

```cpp
template <typename T> constexpr int somepred() { return 14; }

template <typename T> requires (somepred<T>() == 42)            // <=== просиходит вычисление, т.е 14 == 42
bool foo (T&& lhs, T&& rhs) { return lhs < rhs; }

template <typename T>
requires requires (T t) { somepred<T>() == 42; }                // <=== просиходит оценка, т.е. что операция (T == 42) существует
bool bar (T&& lhs, T&& rhs) { return lhs < rhs; }
```

### Что такое `Concept`?

- `requires (T t) { somepred<T>() == 42; }` - вот это условие можно назвать `Concept`. И его можно вынести в переменную типа `concept`.
- https://godbolt.org/z/PG9aYbj6v
- Концепты определяют над собой частичный порядок (частное-общее).

```cpp
requires(T t, U u) {
    u + v;              // true если u + v синтаксически возможно   <=== [simple]   - проверяют интерфейс.
    typename T::inner;  // true если T::inner есть                  <=== [type]     - проверяют наличие типов.
    {*x} -> typename T::inner //                                    <=== [compound] - проверяют совместимость выражений и типов.
    {*x} -> convertible_to<typename T::inner>; //                   <=== [compound] - convertible_to имеет два аргумента. Второй будет подставлен в то, что выведется из x.
    { ++t } noexcept; //                                            <=== [compound] - проверка, что есть ++t и что он не кидает исключения.
    requires sizeof(T) == 4; //                                     <=== [nested]   - вложенные requires. В этом случае внутри форсятся вычисления.
    //                                                                                Т.е. это нужно для того, чтобы сказать концепту, что надо что-то посчитать
}

template<class From, class To>
concept convertible_to =                                // <=== Объявление концепта
    std::is_convertible_v<From, To> &&
    requires(From (&f)()) { static_cast<To>(f()); };

template <typename T> int foo(T x)
requires convertible_to<T, int>                         // <=== Использование концепта

template <Sortable T> void sort(T& t);                  // <=== Можно писать концепт вместо типа. Sortable - это концепт
```

### Карирование аргументов

```cpp
requires(T t, U u) {
    {*x} -> convertible_to<typename T::inner>;                      // <=== просиходит карирование, т.е. получится что-то вроде
                                                                    // convertible_to<decltype(*x), typename T::inner>;
}

template <SomeConcept<int> T> struct S; // SomeConcept<int, T>      // <=== карирование аргументов

```

### Концепты определяют над собой частичный порядок (частное-общее)

- https://godbolt.org/z/shxvK3GWK

```cpp
// RandomAccessIterator : BidirectionalIterator : ForwardIterator : InputIterator

template <InputIterator Iter>                           // <=== [InputIterator] - более общий
int my_distance(Iter first, Iter last) {
    int n = 0;
    while (first != last) { ++first; ++n; }
    return n;
}

template <RandomAccessIterator Iter>                    // <=== [RandomAccessIterator] - более частный
int my_distance(Iter first, Iter last) {
    return last - first;
}
```

## 08. Type Inference (Вывод типов)

### Категории выражений

- **Категории характеризуют выражения, но не типы**.

- Категории выражений:
  - `prvalue`- это рецепт для построения объекта, но не сам объект. **Не имеет локации в памяти**, но может быть преобразовано в `xvalue`.
  - `xvalue` - (Expiring Value) образуется, когда мы вызываем `std::move` на объекте, что означает, что объект **имеет локацию** в памяти и **может быть перемещен**.
  - `lvalue` - (Locator Value) - это объект, который **имеет локацию** в памяти и **не может быть перемещен**.

- Группы категорий
  - `glvalue` = `lvalue` or `xvalue` - это объект, который **имеет локацию** в памяти.
  - `rvalue` = `prvalue` or `xvalue` - это объект, который **может быть перещен**.

### `rvalue` всегда связывается с `modifiable rvalue reference` (`T&&` - `not const T&&`)

- `rvalue` всегда связывается с `modifiable rvalue reference`
- Это очень важное правило, иначе бы в языке ничего не работало.
- Перегрузки 3 и 4 никогда не вызовутся. Вызовы связываются с 1 и 2, потому что там нет `const`.

```cpp
int foo(int &p);   // 1
int foo(int &&p);  // 2
int foo(const int &p);   // 3
int foo(const int &&p);  // 4

int x = 1;
foo(x);  // → 1
foo(1);  // → 2
```

### `RVO` (Return Value Optimization) and `NRVO` (Named RVO)

- `RVO` и `NRVO` часто применяются компиляторами, чтобы повысить производительность кода, уменьшив количество временных объектов и копий

- Пример `RVO` (Return Value Optimization):
  - Компилятор может применить оптимизацию, при которой временный объект `Verbose`, возвращаемый функцией, создается непосредственно в месте назначения
  - (вместо создания временного объекта и затем его копирования).

```cpp
  Verbose foo() {
      return Verbose();
  }
```

- Пример `NRVO` (Named Return Value Optimization):
  - Компилятор может применить оптимизацию, при которой переменная `foo`, возвращаемая функцией, также создается сразу в месте назначения
  - (вместо создания временного объекта и его копирования).

```cpp
  Verbose bar() {
      Verbose foo;
      return foo;
  }
```

### Надо различать вызван ли `decltype` от `имени` или от `выражения`

- Надо различать вызван ли `decltype` от `имени` или от `выражения`.
  - Для `имени` он выводит тип переменной, как она была объявлена.
  - Для `lvalue выражений` он добавляет `&`.
  - Для `xvalue выражений` он добавляет `&&`.
  - Для `prvalue выражений` он ничего не добавляет.

```cpp
// (1) `decltype(name)` выводит тип переменной, как она была объявлена.
int x; decltype(x) t1 = y;  // name -> int

// (2) `decltype(id-expr)` различает категории значений.

// (2.1) Для lvalues он добавляет левую ссылку.
decltype((x)) t2 = y;  // lvalue expr -> int&

// (2.2) Для xvalues он добавляет правую ссылку.
decltype(std::move(x)) t3 = 1;  // xvalue expr -> int&&

// (2.3) Для prvalues он ничего не добавляет.
decltype(x + 0) t4;  // prvalue expr -> int
```

### `decltype(auto)` ведет себя как `decltype`, но при этом выводится из всей правой части

- `decltype(auto)` cовмещает лучшие стороны двух механизмов вывода.
- Вывод типов является **точным**, но при этом **выводится из всей правой части**.
- `decltype(auto)` ведет себя как `decltype`, но при этом выводится из всей правой части.
  - Если правая часть — это имя, то `decltype` работает по правилам работы с именами,
  - а если правая часть — это выражение, то `decltype` работает по правилам работы с выражениями.

```cpp
double x = 1.0;

decltype(x) tmp = x;  // два раза x не нужен
decltype(auto) tmp = x;  // это именно то, что нужно

decltype(auto) tmp = x;     // → double tmp = x;    // <===
decltype(auto) tmp = (x);   // → double& tmp = x;   // <===
```

### `decltype(auto)` разбор примера

- `decltype(auto)` в нижнем примере работает следующим образом.
  - `auto` берет правую часть и возвращает `T&&` от `xvalue`.
  - А `decltype(auto)`, по правилам `decltype`, добавляет еще одну ссылку `&&`, потому что это x-value.
  - Затем происходит сворачивание ссылок, `T&& && -> T&&`.

```cpp
// - Предыдущий вариант:
template <typename T, typename R = std::remove_reference_t<T>&&>
R almost_move(T&& a) {
    return static_cast<R>(a);
}

// - Используем `decltype(auto)`:
template <typename T> decltype(auto) almost_move(T&& a) {
    using R = std::remove_reference_t<T>&&;
    return static_cast<R>(a);               // <=== `decltype(auto)` от xvalue
}
```

### `auto` можно уточнять концептами

```cpp
template <typename T> requires Sortable<T> void sort(T&);   // <=== такой вариант предпочтителен для экспортных методов
template <Sortable T> void sort(T&);

// Аббревированный аргумент.
// Он работает даже для локальных переменных.
void sort(Sortable auto&);                                  // <=== Пример уточнения агрумента концептом

// Это очень полезная техника:
// просто `auto` может быть не слишком понятно...
std::vector<int> V;
std::input_iterator auto In = std::back_inserter(V);        // <=== Пример уточнения локальной переменной концептом
```

### Правила написания правильных ограничений для шаблонов (используйте только позитивные ограничения)

1. Никогда не используйте негативные ограничения. Негативные ограничения ограничивают типы, которые "дурно пахнут", но могут зацепить другие типы, которые вы не хотите пропускать в функцию.
2. Если вы делаете дефолтные значения для аргумента, то указывайте дефолтный тип в шаблоне для этого аргумента.

**Позитивное ограничение**

```cpp
class Customer {
    MyString fst, snd;
public:
    template <typename S1, typename S2 = const char *>
    requires(std::is_convertible_v<S1, MyString>)
    Customer(S1 &&s1, S2 &&s2 = "") :
        fst(std::forward<S1>(s1)), snd(std::forward<S2>(s2)) {}
};
```

## 09. Variadic Templates

### C-style `...`

- [code/tilir_masters/09_10_c-style-dot-dot-dot.cpp](code/tilir_masters/09_10_c-style-dot-dot-dot.cpp)
- C-style `...`
  - (1) `variadic function`:    `void f(int x, ...);`
  - (2) `variadic macros`:      `#define f(x, ...) ...`

```cpp
int sum_all(int nargs, ...)
{
    va_list ap;
    int cnt = 0;
    va_start(ap, nargs);

    for (int i = 0; i < nargs; ++i)
        cnt += va_arg(ap, int);

    va_end(ap);
    return cnt;
}

#define NUMARGS(...) (sizeof((int[]){__VA_ARGS__}) / sizeof(int))
#define DOSUM(...) sum_all(NUMARGS(__VA_ARGS__), __VA_ARGS__)
```

### C++ style `...`

- Вместо `variadic функции` у нас рекурсивный `variadic template`.
- [code/tilir_masters/09_12_variadic_templates.cpp](code/tilir_masters/09_12_variadic_templates.cpp)

```cpp

// ERROR
template <typename T, typename... Ts>
T sum_all(T&& arg, Ts&&... args)
{
    return arg +
        sum_all(args...);   // error: non-const lvalue reference to type 'int' cannot bind to a temporary of type 'int'
                            // T = const int&,      Ts = const int&,    return = const int&
}

// OK - Первый способ починить
template <typename T, typename... Ts>
auto                                    // <=== fix: auto режет тип и выводит return = int - OK
sum_all(T&& arg, Ts&&... args)
{
    return arg + sum_all(args...);
}

// OK - Второй способ починить
template <typename T, typename... Ts>
T
sum_all2(T&& arg, Ts&&... args)
{
    return arg + sum_all(
        std::forward<Ts>(args)...);     // T = int&&,      Ts = int&&,    return = int&& - OK
}

```

### `Variadic Templates` - несколько простых примеров

- https://eel.is/c++draft/temp.variadic

```cpp
// Каждый элемент из `args` применяется дважды: один раз внутри первого вызова `f` и один раз внутри второго
f(f(args...) + f(args)...)  // ->
                            //      f(f(x, y, z) + f(x),
                            //      f(x, y, z) + f(y),
                            //      f(x, y, z) + f(z));

// Каждый элемент `args` комбинируется с другими элементами того же пакета аргументов, создавая несколько вариаций последовательностей.
f(f(args, args...)...)      // ->
                            //      f(x, x, y, z),
                            //      f(y, x, y, z),
                            //      f(z, x, y, z);
```

### `Variadic Templates` - более сложные примеры

- Как корректно раскрыть пакет аргументов (`parameter pack`) с использованием конструкции `expand_t`, которая помогает избежать проблем с простым раскрытием пакета через запятую.
- `void()` используется для создания пустого выражения, чтобы предотвратить выполнение перегруженного оператора `operator,`.

**Иногда случаи, которые кажутся простыми, не работают.**

```cpp
template <typename ... T>
void foo(T ... ts) {
    bar(ts)...;
}
```

**Настоящий метод выглядит куда интересней.**

```cpp
struct expand_t {
    template <typename ... T>
    expand_t(T...) {}
};

template <typename ... T>
void foo(T ... ts) {
    expand_t{(bar(ts), void(), 0)...};
}
```

### Документация по паттернам раскрытия

- https://eel.is/c++draft/temp.variadic

### Экзотические свертки

- https://godbolt.org/z/j9YPnvdjs

```cpp
template <typename T> struct Node {
  T data;
  Node *left = nullptr;
  Node *right = nullptr;
};

template<class T, class... Args>
Node<T> *tree_get(Node<T> *top, Args... args) {
  return (top ->* ... ->* args);                    // <===
}

TEST(variadic, exoticfold) {
  Node<int> t[5];
  t[0].left = &t[1];
  t[1].left = &t[2];
  t[2].right = &t[3];
  t[3].data = 5;
  auto left = &Node<int>::left;                     // <===
  auto right = &Node<int>::right;                   // <===
  auto *res = tree_get(&t[0], left, left, right);
  EXPECT_EQ(res->data, 5);
}
```

### Светрки с пустыми пачками тоже работают

- https://godbolt.org/z/z4h9E6ME9
- [code/tilir_masters/09_14_variadic_templates_empty_pack.cpp](code/tilir_masters/09_14_variadic_templates_empty_pack.cpp)
- Пустая пачка для `&&` - это `true`, а для `||` - `false`.
- Пустая пачка для `+` вызывает ошибку компиляции.

```cpp
template <typename... Ts>
auto sum_all(Ts... args)
{
    return (... + args); // error: unary fold expression has empty expansion for operator '+' with no fallback value
}

template <typename... Ts>
auto and_all(Ts... args)
{
    return (... && args); // OK => true
}
```

### `std::conjunction_v` - проверка всех типов на истинность

- `std::conjunction` — это логическое "и" для типов, которое используется в работе с вариативными шаблонами (variadic templates).

```cpp
template <typename T, typename ... TS>
constexpr inline bool are_same_v = std::conjunction_v<std::is_same<T, TS>...>; // <===

template <typename ... TS>
auto sum_all(TS&& ... args)
    requires are_same_v<TS...>                  // <===
{
    return (... + std::forward<TS>(args));
}

TEST(variadic, cstyle) {
    int res;
    res = sum_all(1, 2, 3, 4);
    EXPECT_EQ(res, 10);
}

```

### Вариабельные концепты и каррирование

```cpp
// Базовый концепт для пачки параметров - это свертка
template <typename ... Ts>
    requires (EqualityComparable<Ts> && ... && true)
void f(Ts ... ts);

// Если переписать через шаблонный параметр, то он будет сворачивать с true
template <EqualityComparable ... Ts>    // <===
void f(Ts ... ts);

// Если есть дополнительные аргументы
template <typename ... Ts>
    requires (ConvertibleTo<Ts, int> && ... && true)
void f(Ts ... ts);

// При указании в шаблоне работает КАРРИРОВАНИЕ
template <ConvertibleTo<int> ... Ts> // ok      <=== Тут типы подставляются перед int: ConvertibleTo<Ts, int>
void f(Ts ... ts);
```

### Свертки очень важны для концептов, так как у нас нет рекурсии и выхода (нет откусывания пачки)

- На слайде показан пример реализации одного и того же через откусывание первого параметра из пачки и без откусывания, но с использованием сверток.
- Важно отметить, что откусывание запрещено в концептах, поэтому если мы пишем концепт для пачки, то мы можем использовать только свертку.
- В концептах нельзя метапрограммировать. Это свойство запрещено, потому что `requires` — это хук разрешения имён, а метапрограммирование разрешено только на этапе инстанцирования.

```cpp
template <typename T, typename ... Ts>
concept Addable = requires(T&& arg, Ts&& ... args) {
    arg + Addable(std::forward<Ts>(args)...);           // FAIL - откусывание в концептах запрещено
}

template <typename ... Ts>
concept Addable = requires(Ts&& ... args) {
    (std::forward<Ts>(args) + ...);                     // OK - свертка в концептах разрешена
}

template <typename T, typename ... Ts>
auto sum_all(T&& arg, Ts&& ... args) {
    if constexpr(sizeof...(args) != 0)
        return arg + sum_all(std::forward<Ts>(args)...); // OK - откусывание в шаблонных функциях разрешено
    return 0;
}

template <typename ... Ts>
auto sum_all(Ts&& ... args) {
    return (std::forward<Ts>(args) + ...);              // OK - свертка в шаблонных функциях разрешена
}
```

### Пачка параметров обычно должна идти последним аргументом, т.к. из за жадности она заберет все последующие аргументы

- https://godbolt.org/z/77PEx6xsj
- https://godbolt.org/z/KsM1Kjhrr

```cpp
// ОШИБКА
template <typename T> class Stack {
  struct StackElem {
    T elem;
    StackElem *next;
    StackElem(T e, StackElem *nxt) : elem(e), next(nxt) {}  // <===

    template <class... Args>
    StackElem(Args &&... args, StackElem *nxt)              // <=== ERROR: Пачка параметров съест StackElem *nxt
        : elem(std::forward<Args>(args)...), next(nxt) {}   //      Поэтому будет вызыван конструктор StackElem(T e, StackElem *nxt)
  };

// ---

// ИСПРАВЛЕНИЕ
template <typename T> class Stack {
  struct StackElem {
    T elem;
    StackElem *next;
    StackElem(StackElem *nxt, T e) : elem(e), next(nxt) {}

    template <class... Args>
    StackElem(StackElem *nxt, Args &&... args)              // <=== Пачка параметров идет после StackElem *nxt, все хорошо!
        : elem(std::forward<Args>(args)...), next(nxt) {}
  };

```

### Пример с `auto` для вывода указателя на поле класса

- [code/tilir_basics/template_fold_examples.cpp](code/tilir_basics/template_fold_examples.cpp)
- https://godbolt.org/z/j9YPnvdjs

```cpp
// Шаблон для перемещения по дереву, указывая левый или правый указатель.
template <typename T>
struct Node
{
    T data;
    Node* left;
    Node* right;
};

template <typename Node, typename First, typename... Rest>
Node* get_tree(Node* node, First first, Rest... rest)
{
    return get_tree(node->*first, rest...);
}

auto left = &Node<int>::left;                   // <===
auto right = &Node<int>::right;                 // <===
auto subTree = get_tree(root, left, right);
```

## 10. Lambda-выражения

### Синтаксис `->` для указания типа возвращаемого значения (C++11)

- Основная мотивация: простота вывода из типов аргументов.
- Также этот синтаксис работает для `λ-выражений`.
- Объект `adder` – это объект `closure`. Собственно, в лямбде функции через стрелочку можно указать тип, который она возвращает, но это опционально. Она может вывести сама тип, по аналогии как это делает `auto`.

```cpp
auto foo() { return 2.0; }                                  // <=== есть вывод типа
auto foo() -> int { return 2.0; }                           // <=== нет вывода типов

auto foo(std::input_iterator auto inp) -> decltype(*inp)    // <=== пользовательский вывод типа
{ ..... }

auto adder = [](int x, int y) -> int { return x + y; };     // <=== применяется в лямбда-выражениях
```

### Что такое `λ-выражение` и `closure` без захвата

- `Lambda-выражение` без захвата - это объект `closure` с перегруженным `оператором приведения` к указателю на функцию.
- Если у лямбда нет состояния, то это, по сути, статический метод. Это делается, чтобы экономить лишний вызов по указателю.
- Также это позволяет использовать лямбду вместо указателя на функцию.

```cpp
auto adder = [](int x, int y) -> int { return x + y; };

struct Closure {
  static int func(int x, int y) { return x + y; }
  using func_t = std::decay_t<decltype(func)>;
  operator func_t() const { return func; }          // <=== оператор приведения типа
};

int (*pf)(int x, int y) = adder; // implicit cast   // <=== такой код будет работать
```

### `std::invoke` и callable объекты

- [code/tilir_masters/10_10_std_invoke.cpp](code/tilir_masters/10_10_std_invoke.cpp)
- Для вашего обобщённого кода он абстрагирует callables, включая stateful.
- Т.е. вместо вызова `obj()` можно использовать `std::invoke(obj)`.
- `std::invoke` позволяет также получать доступ к полям класса.

```cpp
struct S {
  int n = 2;
  int foo(int y) { return 3; }
};

auto psf = &S::foo;                  // <=== указатель на метод класса
auto psn = &S::n;                    // <=== указатель на поле класса

auto r1 = std::invoke(foo, 1);
auto r2 = std::invoke(psf, s, 1);
auto r3 = std::invoke(psf, &s, 1);
auto r4 = std::invoke(psn, s);      // <=== возвращает значение поля
```

### `std::invoke` и указатель на поле класса

- Благодаря магии `invoke`, лямбды иногда сводятся к проекторам.
- Указатель на поле класса — это особый вид указателя, который не вызывает функцию, а просто возвращает значение этого поля.
- Это полезно в обобщённом коде, когда, например, нужно передавать проекции, а не писать сложные лямбды.

```cpp
template <typename Range, typename Callable>
void print_range(Range r, Callable c) {
    for (auto e : r)
        std::cout << std::invoke(c, e) << " ";
    std::cout << std::endl;
}

std::vector<std::pair<int, int>> v = {{1, 1}, {2, 2}, {3, 3}};
print_range(v, [](const std::pair<int, int> &p)
    { return p.second; });                              // <=== проекция на второй элемент

print_range(v, &std::pair<int, int>::second);           // <=== проекция на второй элемент
```

### Positive Lambda Hack

- Интересно, что кложура не копируема (но copy-конструируема), а указатель на функцию копируема.
- `Positive Lambda Hack` заключается в использовании оператора `+` перед лямбда-функцией для явного вызова приведения кложуры к типу указателя на функцию. Это приводит к тому, что хранится не уникальная кложура, а указатель на функцию, который можно заменять другим указателем на функцию.

```cpp
auto test = []{};
test = []{};          // FAIL

auto test = +[]{};    // OK - positive lambda hack - вызов приведения типов руками.
test = +[]{};
```

### Generic Lambda - это лямбда-функция с шаблонным оператором приведения

- Аналогичный код внизу (он не компилируется). Проблемы в коде решены в `generic lambda`.
- https://godbolt.org/z/58Y5vffG5

```cpp
struct Capture {
  template <typename T, typename U>
  static auto func(T x, U y) { return x + y; };

  template <typename T, typename U>
  using func_t = std::decay_t<decltype(func<T, U>)>;

  template <typename T, typename U>
  operator func_t<T, U>() { return func; }
};

TEST(lamdas, callables) {
  Capture c;
  auto res = c(1, 1.0);
  EXPECT_EQ(res, 2);
}
```

### `decltype([](auto x) { return 2 * x; })` - лучший способ запомнить lambda тип (С++20)

- https://godbolt.org/z/fzv9oGPx1
- Этот трюк построен на ленивом инстанцировании шаблонов.

```cpp
decltype([](auto x) { return 2 * x; }) twice;   // <=== это объект типа лямбда
auto x = twice(2); // x == 4
```

### Явные шаблонные аргументы (С++20)

- Синтаксис явных шаблонных аргументов для лямбда-функций позволяет добавлять концепты, которые могут зависеть от нескольких типов.
- В этом примере используются все виды скобок в языке.

```cpp
auto l = []<typename T, typename U>(T x, U y)         // <===
        requires Addable<T, U> { return x + y; };
```

### Лямбда-функции c захватом

- При наличии захвата, обобщённое λ-выражение — это структура с оператором вызова.
- Теперь поговорим про лямбда-функции с захватом.
- В них уже нет оператора приведения к указателю на функцию. В них **есть оператор круглых скобок**.
- Для отключения `const` в захвате используется `mutable`: `auto l = [x = 1]() mutable { x = 2; };`.
- Захват по ссылке: `auto l = [&x]() { x = 2; };`. Можем менять `x` даже без `mutable`.
- Захват по значению: `auto l = [x]() { x = 2; };`.
- Лайфхак для захвата по константной ссылке: `auto l = [const& x]() { x = 2; };`.
- Захват по константной ссылке: `auto l = [&x = std::as_const(x)]() { x = 2; };`.

```cpp
int a = 2, b = 3;
auto parm_adder = [a, b]                        // <===
    (int x, int y) {
        return x * a + y * b;
};

struct Closure {
    int a_, b_;
    Closure(int a, int b) : a_(a), b_(b) {}
    auto operator()(int x, int y)
        const                                   // <===
        { return x * a_ + y * b_; }
};
```

### Захват c явным переименованием

- https://godbolt.org/z/aGP1xqh5W
- https://godbolt.org/z/cTc3oj4x7 - константные ссылки должны же связываться с rvalue-ссылками?

```cpp
int a = 1;
auto lmd = [&ra = a, va = a] { return va + ra; };   // <=== хороший тон это явное переименование

std::vector b = {1, 2, 3};
auto lmd2 = [vb = std::move(b)] { return vb; };     // <=== даёт возможность move-захвата
                                                    //      полее vb внутри замыкания это value
```

### Илучшаем свой идеальный проброс

- https://godbolt.org/z/co8YYqsPM
- Добавляя `std::invoke` мы по сути получаем ничем не отличающийся собственный метод от `std::invoke`.
- Внезапно мы оказались на двух стульях.

```cpp
template<typename Fun, typename... Args>
decltype(auto) transparent(Fun&& fun, Args&&... args) {
    return std::forward<Fun>(fun)                               // <=== Добавляем std::forward
        (std::forward<Args>(args)...);
}

template<typename Fun, typename... Args>
decltype(auto) transparent(Fun&& fun, Args&&... args) {
    return std::invoke                                          // <=== Добавляем std::invoke
        (std::forward<Fun>(fun), std::forward<Args>(args)...);
}
```

### Захват с вариабельными пачками (C++20)

- [code/tilir_masters/10_20_lambda_and_folds.cpp](code/tilir_masters/10_20_lambda_and_folds.cpp)

```cpp
template <typename ... Args>
int foo(Args ... args) {
  auto lm1 = [args...] { return sizeof...(args); };                 // возможность раскрыть пачку в списке инициализации
  auto lm2 = [...xs = args] { return sizeof...(xs); };              // перекладывание пачки в пачку
  auto lm3 = [&...xs = args] { return sizeof...(xs); };             // захват пачки с capture reference (сделали все ссылками)
  auto lm4 = [...xs = std::move(args)] { return sizeof...(xs); };   // захват пачки с переименованием (move каждого элемента)
  return lm1() + lm2() + lm3() + lm4();
}
```

### Карирование функции - это частичная подстановка ее аргументов

- **Классическое** карирование - это **подстановка в конец**.

```cpp
// ЗАДАЧА: Написать функцию curry, которая частично применяет аргументы к функции
auto add = [](auto x, auto y) { return x + y; }
auto add4 = curry(add, 4);
assert(add4(11) == 15);

// РЕШЕНИЕ
template <typename Fun, typename... Args>
auto curry(Fun fun, Args... args)                   // <=== Съедаем первую часть аргументов
{
    return [=](auto... rest)                        // <=== Съедаем все остальные аргументы
    {
        return std::invoke(fun, args..., rest...);  // <=== Восстанавливаем вызов со всеми аргументами
    };
}
```

### Захватывается только локальный нестатический контекст

- [code/tilir_masters/10_24_lambda_local_context.cpp](code/tilir_masters/10_24_lambda_local_context.cpp)

```cpp
int g = 1;              // <=== не копируется в лямбду, т.к. глобальная.

void foo(int b)
{
    int x = 2;
    static int a = 3;   // <=== не копируется в лямбду, т.к. статическая.
    if (b == 4)
    {
        int y = 5;
        auto lam = [=]
        {
            return x + y + a + b + g;
        };

#if INCREMENT_ALL_VARIABLES
        // здесь изменения x, y, b уже не изменят результат
        // зато изменения a и g − изменят
        g++; b++; x++; a++; y++;
#endif

        std::cout << lam() << std::endl;
    }
```

**ПРИМЕР НА ПОНИМАНИЕ**

- [code/tilir_masters/10_24_lambda_local_context.cpp](code/tilir_masters/10_24_lambda_local_context.cpp)

```cpp
auto factory(int parameter)
{
    static int a = 0;           // Этот член будет общим

    return [=](int argument)    // <=== Этот вызов всегда возвращает один и тот же класс
    {
        static int b = 0;       // Этот член будет общим
        a += parameter;
        b += argument;
        return a + b;
    };
}

int main()
{
    auto func1 = factory(1);
    auto func2 = factory(2);
    std::cout << func1(20) << " " << func1(30) << " " << func2(20) << " " << func2(30) << std::endl;
}
```

### Четыре способа создать `std::tuple`

1. конструктор
2. `tuple<VTypes...> make_tuple(Types&&...)` - создает tuple с автовыводом типов. Похож на захват по значению.
3. `tuple<CTypes...> tuple_cat(Tuples&&...)` - конкатенация - рассыпаем и захватываем.
4. `tuple<Types&...> tie(Types&...)` - создает ссылки на переменные.
5. `tuple<T&&...> forward_as_tuple(T&&...)` - берет T&& и форвардит его в T&&.

```cpp
// 1. конструктор
std::tuple<int, double, std::string> t1(1, 2.0, "3");

// 2. make_tuple
auto t2 = std::make_tuple(1, 2.0, "3");

// 3. tuple_cat
auto t3 = std::tuple_cat(t1, t2, std::make_pair(1, 2));
assert(t3 == std::make_tuple(1, 2.0, "3", 1, 2.0, "3", 1, 2));

// 4. tie
int a; double b; std::string c;
auto t4 = std::tie(a, b, c);

int c; double d;
std::tuple<int, double> foo();
std::tie(c, d) = foo();                 // <=== Через ссылки на переменные записали в них значения.

// Сокращенный синтаксис std::tie - structured binding (C++17)
auto [c, d] = foo();
auto && [c, d] = foo();                 // <=== rvalue

int a[2] = {1, 2};
auto& [xr, yr] = a;                     // <=== Работает и для массивов

struct { int x; double y; } s = {1, 2.0};
const auto& [xcr, ycr] = s;             // <=== Работает на любых классах, у которых открыты все нестатические элементы

// Связывание для собственных классов
// Чтобы поддержать связывание для собственного класса, необходимо определить специализации для всего трёх функций
class Config {
    int x; double y; std::string z;
    // открытые члены, включая геттеры вида get_x(), get_y() и get_z()
};
template<> struct tuple_size<Config>: integral_constant<size_t, 3> {};  // <=== 1. Размер tuple
template<> decltype(auto) get<0>(Config& c) { return c.get_x(); }       // <=== 2. get
template<> struct tuple_element<0, Config> { using type = int; };       // <=== 3. Тип элемента
// Теперь будет работать (нужно добавить get для остальных).
auto [id, value, name] = get_config();                                  // <=== Результат

// 5. forward_as_tuple
auto t5 = std::forward_as_tuple(1, 2.0, "3");
```

### `std::forward_as_tuple` для решения проблемы форвардинга пачки агрументов в лямбда захват

- [code/tilir_masters/10_28_lambda_perfect_forward_fail.cpp](code/tilir_masters/10_28_lambda_perfect_forward_fail.cpp)
- [code/tilir_masters/10_30_lambda_perfect_forward_custom_wrapper.cpp](code/tilir_masters/10_30_lambda_perfect_forward_custom_wrapper.cpp)
- [code/tilir_masters/10_32_lambda_perfect_forward_tuple_custom.cpp](code/tilir_masters/10_32_lambda_perfect_forward_tuple_custom.cpp)
- [code/tilir_masters/10_34_lambda_perfect_forward_forward_as_tuple.cpp](code/tilir_masters/10_34_lambda_perfect_forward_forward_as_tuple.cpp)

```cpp
auto foo = []<typename ... T>(T&&... a)
{
    return
        [a = std::forward_as_tuple(a...)]       // <=== Форвардим каждый элемент в пачке
        () mutable
    {
        return ++std::get<0>(a);
    };
};
```

### `std::apply` - для применения функции к каждому агрументу

- [code/tilir_masters/10_36_std_apply.cpp](code/tilir_masters/10_36_std_apply.cpp)

```cpp
auto add = [](auto x, auto y) { return x + y; };
auto sum1 = std::apply(add, std::pair(1, 2));
EXPECT_EQ(sum1, 3);

auto mult = std::apply( [](auto&&... xs)
                            { return (1 * ... * xs); },
                        std::make_tuple(1, 2, 3, 4, 5));
EXPECT_EQ(mult, 120);

// for_each для каждого элемента tuple
// форвардинг добавить самостоятельно и починить ошибки компиляции TODO
// auto fn = add;
// auto t = std::make_tuple(1, 2, 3.0, 4);
// auto sum2 = std::apply([&fn](auto&& ... xs) {(fn(xs), ...);}, t);
// EXPECT_EQ(sum2, 10.0);
```

### `std::any` - стирает типы

- Превращает С++ в Python.
- [code/tilir_masters/10_38_std_any_type_erasure.cpp](code/tilir_masters/10_38_std_any_type_erasure.cpp)

```cpp
std::any a = 1;
EXPECT_EQ(std::any_cast<int>(a), 1);
EXPECT_EQ(a.has_value(), true);
a.reset();
EXPECT_EQ(a.has_value(), false);
auto h = std::make_any<HeavyObject>(100);
```

### `std::variant` - альтернатива `std::any`, которая хранит только один из заданных типов

- [code/tilir_masters/10_40_std_variant.cpp](code/tilir_masters/10_40_std_variant.cpp)

```cpp
std::variant<int, float> v = 12;
EXPECT_EQ(std::get<int>(v), 12);
EXPECT_EQ(std::holds_alternative<float>(v), false);

std::vector<std::variant<int, float, std::string>> vec = {10, 1.5f, "hello"};

for (auto& v : vec)
{
    std::visit(
        [](auto&& arg)
        {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, int>) // <=== Используем if constexpr, чтобы делать специфичные для
                                                    //      типов операции.
            {
                std::cout << arg % 5 << std::endl;
            }
            else if constexpr (std::is_same_v<T, float>)
            {
                std::cout << "I am a float " << std::round(arg) << std::endl;
            }
        },
        v);
}
```
