- [Not Sorted Notes](#not-sorted-notes)
- [Заметка о RVO и конструкторах копирования](#заметка-о-rvo-и-конструкторах-копирования)
- [Заметка о volatile](#заметка-о-volatile)
- [Про `operator->`](#про-operator-)
- [Заметка про R-Value и L-Value ссылки и выражения. `std::move`](#заметка-про-r-value-и-l-value-ссылки-и-выражения-stdmove)
- [Note on Move Semantics and `std::exchange`](#note-on-move-semantics-and-stdexchange)
- [Move Assignment Operator Implementation](#move-assignment-operator-implementation)
- [Why Self-assignment Check is Not Required for Move Assignment Operator](#why-self-assignment-check-is-not-required-for-move-assignment-operator)
- [Default Special Member Functions Generation](#default-special-member-functions-generation)
- [Заметка: Правило Нуля и Правило Пяти](#заметка-правило-нуля-и-правило-пяти)
- [Forwarding References and Perfect Forwarding](#forwarding-references-and-perfect-forwarding)
- [Forwarding References Example](#forwarding-references-example)
- [Заметка: Как устроен `std::move`](#заметка-как-устроен-stdmove)
- [Опасности Forwarding References](#опасности-forwarding-references)
- [Overloading set using Forwarding References](#overloading-set-using-forwarding-references)
- [`std::move` may prevent Return Value Optimization (RVO)](#stdmove-may-prevent-return-value-optimization-rvo)
- [Copy-and-Swap to the Rescue!](#copy-and-swap-to-the-rescue)
- [Copy-and-Swap приводит к дублированию](#copy-and-swap-приводит-к-дублированию)
- [By-Value Assignment Operator](#by-value-assignment-operator)
- [Правило четырех с половиной (Rule of Four and a Half)](#правило-четырех-с-половиной-rule-of-four-and-a-half)
- [Complete Vector Implementation with Comments](#complete-vector-implementation-with-comments)
- [Perfect Forwarding and Universal References (Josuttis Explanation)](#perfect-forwarding-and-universal-references-josuttis-explanation)
- [Explanation of the Slide with `enable_if` and SFINAE in C++17](#explanation-of-the-slide-with-enable_if-and-sfinae-in-c17)
- [Функторы быстрее указателей в Лямбда-выражениях](#функторы-быстрее-указателей-в-лямбда-выражениях)
- [Указатели на методы классов](#указатели-на-методы-классов)
- [Fold Expressions](#fold-expressions)
- [chrono DATES](#chrono-dates)
- [Таблица виртуальных функций (vtable)](#таблица-виртуальных-функций-vtable)
- [Empty Base Class Optimizations (EBCO)](#empty-base-class-optimizations-ebco)
- [EBCO и unique\_pointer](#ebco-и-unique_pointer)
- [Аргументы по умолчанию связываются статически (важно для виртуальных методов)](#аргументы-по-умолчанию-связываются-статически-важно-для-виртуальных-методов)
- [Non-Virtual Interface (NVI) Pattern - решение проблемы с аргументами по умолчанию для виртуальных методов](#non-virtual-interface-nvi-pattern---решение-проблемы-с-аргументами-по-умолчанию-для-виртуальных-методов)
- [Pure Virtual Call](#pure-virtual-call)
- [Два полиморфизма](#два-полиморфизма)
- [Перегрузка виртуальных функций](#перегрузка-виртуальных-функций)

### Not Sorted Notes

- Если добавить 1 к указателю на массив, то у нас произойдет **скачок равный размеру массива**.
- **Манглирование**, которое существует в языке C++, позволяет делать перегрузку функций, добавлять методы к классам, и создавать семейство шаблонных функций. Язык C, в отличие от C++, не имеет манглирования, но он имеет **строгую гарантию по именам**. Поэтому язык C используется для создания согласованных API.
- Использование **анонимных пространств имён** позволяет определять методы, которые видны только внутри данного CPP файла. Это делает их как бы статическими методами.
- **Список инициализации** выполняется в том порядке, в котором вы написали поля класса.
- Если мы **самостоятельно управляем ресурсами**, которые не управляются автоматически (например, голые указатели в классе), то необходимо правильно реализовать **конструктор копирования и оператор присваивания**. Самый простой способ реализовать эти конструкторы – это **запретить их через ключевое слово `delete`**.

```cpp

class MyClass {
public:
    MyClass(const MyClass&) = delete;
    MyClass& operator=(const MyClass&) = delete;

    // Остальная реализация класса...
};

```

- Класс в C++ можно рассматривать как набор методов для работы с инкапсулированными данными. Если мы говорим о **RAII-классе**, то этот набор методов не влияет на состояние объекта, а лишь **предоставляет правильный интерфейс к ресурсу**, доступ к которому мы защищаем.
- **Default move constructor also noexcept**.

```cpp

class Widget {
private:
    int i{0};
    std::string s{};
    std::unique_ptr<int> p{};

public:
    // Move constructor
    Widget(Widget&&) = default; // Note: also noexcept!
};

```

### Заметка о RVO и конструкторах копирования

- Конструктор копирования может быть выброшен на уровне фронтенда языка. На этом основана специальная семантика копирования (**RVO, Return Value Optimization**).

RVO (Return Value Optimization) основана на том, что операторы копирования и присваивания должны всегда создавать **эквивалентный объект**. Если в операторах копирования или присваивания добавлена логика, например, форматирование диска, которая не должна пропускаться при RVO, это становится проблемой разработчика. **Компилятор имеет право выбрасывать эти методы для оптимизации кода.**

Пример кода, показывающий выбрасывание конструктора копирования:
- В этом примере может быть вызван только конструктор, а не конструктор копирования, благодаря RVO.
- Важно помнить, что если в вашем операторе копирования или присваивания содержится дополнительная логика, которая должна быть выполнена, вы не можете полагаться на то, что компилятор не выбросит эти методы.

```cpp

MyClass CreateMyClass() {
    return MyClass();  // Здесь компилятор может выбросить вызов конструктора копирования благодаря RVO
}

int main() {
    MyClass obj = CreateMyClass();
    return 0;
}

```

### Заметка о volatile

Слово `volatile` в языке C++ означает, что объект может измениться непредсказуемым образом, независимо от вашего кода. Это может произойти, например, из-за воздействия внешних процессов, прерываний, или аппаратных устройств.

Использование `volatile` говорит компилятору не оптимизировать доступ к этому объекту, поскольку он может измениться в любое время.

Пример:

```cpp
volatile int sensorValue;

// Ожидание изменения значения сенсора
while (sensorValue == 0) {
    // Здесь не будет оптимизации цикла, потому что sensorValue может измениться вне кода
}
```

В этом примере компилятор не будет оптимизировать цикл, полагая, что значение `sensorValue` не изменится, поскольку оно помечено как `volatile`.

### Про `operator->`

- **Оператор «стрелочка» не позволяет получать доступ к указателю, который она возвращает, но дает доступ к полям данного объекта по указателю.**

Оператор стрелочка (`operator->`) действительно позволяет предоставить доступ к полям или методам объекта, на который указывает возвращаемый указатель. Это используется, чтобы предоставить доступ к внутренним объектам класса.

Вот пример, демонстрирующий использование оператора стрелочка для доступа к полям внутреннего объекта:

```cpp
#include <iostream>

class Inner {
public:
    int value;

    Inner(int v) : value(v) {}

    void Display() const {
        std::cout << "Inner value: " << value << std::endl;
    }
};

class Outer {
private:
    Inner* inner;

public:
    Outer(int v) : inner(new Inner(v)) {}

    ~Outer() {
        delete inner;
    }

    // Определение пользовательского оператора `->`
    Inner* operator->() {
        return inner;
    }

    const Inner* operator->() const {
        return inner;
    }
};

int main() {
    Outer outer(42);
    outer->Display(); // Использование пользовательского оператора `->` для доступа к методу Display
    std::cout << "Inner value accessed through operator->: " << outer->value << std::endl;

    const Outer constOuter(100);
    constOuter->Display(); // Использование константного пользовательского оператора `->`

    return 0;
}
```

### Заметка про R-Value и L-Value ссылки и выражения. `std::move`

- **L-value** в C++ означает Location Value, т.е. значение, которое имеет локацию.
- "Операция «Взятие выражения», «Связывание выражения с ссылкой» и в этот момент **материализация этого выражения называется R-value ссылкой**."

```cpp

int&& y = x + 1;

```

- **Const L-value reference продляет жизнь временного объекта**, позволяя нам ссылаться на него до конца его существования.
- **Const R-value reference, по сути, создает временный объект и дает ему жизнь**, связываясь с этим временным объектом и продлевая его срок жизни до конца блока, где эта ссылка используется.

```cpp

int x = 5;
const int& lRef = x + 1; // L-value reference продляет жизнь временного объекта (x + 1)
const int&& rRef = x + 1; // R-value reference создаёт временный объект и продлевает его жизнь

```

- **`std::move`** – это, по сути, приведение ссылки `T&` (L-value reference) к ссылке `T&&` (R-value reference).

```cpp
int x = 5;
int&& rRef = std::move(x); // std::move привел int& к int&&
```

```cpp
#include <iostream>
#include <utility>

void PrintAndReset(int&& value)
{
    std::cout << "Value: " << value << std::endl;
    value = 0;
}

int main()
{
    int x = 5;
    PrintAndReset(std::move(x)); // Приводим int& к int&&, используя std::move
    std::cout << "x after move: " << x << std::endl;
    return 0;
}
```

- Правые ссылки (R-value references) дают нам возможность отличать объекты, которые мы не готовы перемещать или модифицировать (L-value references), от объектов, которые мы можем безопасно перемещать или временно использовать (R-value references). При этом **правая ссылка сама по себе задает имя и адрес и является L-value**.
- После применения `std::move` объект переходит в **неконсистентное, но предсказуемое состояние**. В этом состоянии объект может корректно завершить свою жизнь. Либо этот объект можно переиспользовать.

### Note on Move Semantics and `std::exchange`

- `std::exchange` удобно применять к сырым указателям.
- В контексте move-семантики удобно использовать **`std::exchange`, чтобы обмениваться значениями**,
- и желательно указывать атрибут **`noexcept`** для move функций, если они не выкидывают исключений. Это **ускорит работу библиотечными контейнерами**

In the context of move semantics, it is convenient to use `std::exchange` to swap values. It is also recommended to mark move functions with the `noexcept` attribute if they do not throw exceptions. This can improve the performance when using standard library containers.

```cpp

#include <utility> // for std::exchange
#include <string>

class MyClass {
public:
    MyClass(std::string data) : data_(std::move(data)) {}

    // Move constructor
    MyClass(MyClass&& other) noexcept
        : data_(std::exchange(other.data_, "")) {}

    // Move assignment operator
    MyClass& operator=(MyClass&& other) noexcept {
        if (this != &other) {
            data_ = std::exchange(other.data_, "");
        }
        return *this;
    }

private:
    std::string data_;
};

```

In this example, `std::exchange` is used to swap the internal state of the objects during the move operations. The `noexcept` specifier is added to indicate that these move operations do not throw exceptions, which can enhance performance with standard library containers.

The slide in question shows an implementation of the move assignment operator without an explicit self-assignment check. Let's break down why this might be the case and the general approach to implementing such an operator.

### Move Assignment Operator Implementation

#### Goal:

- Clean up all visible resources.
- Transfer the content of `w` into `this`.
- Leave `w` in a valid but undefined state.

#### Example:

```cpp
class Widget {
private:
    int i{0};
    std::string s{};
    int* pi{nullptr};

public:
    // Move assignment operator
    Widget& operator=(Widget&& w) noexcept {
        delete pi; // Phase 1: Cleanup

        i = std::move(w.i); // Phase 2: Member-wise move
        s = std::move(w.s);
        pi = std::move(w.pi);

        w.pi = nullptr; // Phase 3: Reset

        return *this;
    }

    // Other member functions...
};
```

### Why Self-assignment Check is Not Required for Move Assignment Operator

ENG: Move semantics are designed to transfer ownership of resources from one object to another, effectively leaving the source object in a valid but unspecified state. **This transfer does not require any action if an object is moved into itself**.

```cpp

// Move assignment operator
Widget& operator=(Widget&& w) noexcept {
    delete pi; // Phase 1: Cleanup

    i = std::move(w.i); // Phase 2: Member-wise move
    s = std::move(w.s);
    pi = std::move(w.pi);

    w.pi = nullptr; // Phase 3: Reset

    return *this;
}

```

In the case of a move assignment operator, self-assignment checks are generally not needed because:
1. **Move Semantics:** If `w` is an rvalue, it should generally be a temporary object, making self-assignment unlikely. However, if `w` is an lvalue (which can happen), the move assignment typically leaves `w` in an unspecified state, but still valid.
2. **Standard Library Compliance:** The use of `std::move` and reset of `w` ensure that resources are correctly transferred and that `w` is left in a safe state, preventing issues even if self-assignment were to occur.

However, it is important to note that including a self-assignment check can sometimes be beneficial, especially in more complex classes or to follow best practices in defensive programming.

```cpp

Widget& operator=(Widget&& w) noexcept {
    if (this != &w) {
        delete pi; // Phase 1: Cleanup

        i = std::move(w.i); // Phase 2: Member-wise move
        s = std::move(w.s);
        pi = std::move(w.pi);

        w.pi = nullptr; // Phase 3: Reset
    }
    return *this;
}
```

This approach is generally safe and ensures that the object is correctly handled even in the unlikely event of self-assignment.

### Default Special Member Functions Generation

1. **Default Move Operations Generation:**
   - The default move operations (move constructor and move assignment operator) are automatically generated by the compiler **if no copy operation** (copy constructor or copy assignment operator) **or destructor** is user-defined.

2. **Default Copy Operations Generation:**
   - The default copy operations (copy constructor and copy assignment operator) are automatically generated by the compiler **if no move operation** (move constructor or move assignment operator) is user-defined.

3. **User-defined Count:**
   - Using `=default` or `=delete` in the definition of these operations counts as user-defined. This affects the automatic generation of other special member functions.

### Заметка: Правило Нуля и Правило Пяти

**Правило Нуля:**
- Вы не определяете никаких специальных методов (конструкторов, деструкторов, конструкторов копирования, операторов копирования/перемещения).
- Компилятор генерирует все необходимые функции за вас, обеспечивая эффективное и безопасное управление ресурсами.

**Правило Пяти:**
- Если вы определяете один из следующих методов: деструктор, конструктор копирования, оператор копирования, конструктор перемещения, или оператор перемещения, то следует определить все пять.
- Это гарантирует корректное и консистентное управление ресурсами вашего класса, избегая проблем с утечками ресурсов или двойным удалением.

```cpp
class MyClass {
public:
    ~MyClass(); // Деструктор
    MyClass(const MyClass&); // Конструктор копирования
    MyClass& operator=(const MyClass&); // Оператор копирования

    MyClass(MyClass&&); // Конструктор перемещения
    MyClass& operator=(MyClass&&); // Оператор перемещения
};
```

### Forwarding References and Perfect Forwarding

Forwarding References позволяет передавать параметры в функции шаблонов без потери их типа и категорийности (lvalue или rvalue). Это особенно полезно при написании оберток вокруг конструкторов или других функций, принимающих параметры по ссылке. Это достигается путем использования синтаксиса T&& или auto&&.

**Perfect Forwarding** можно рассматривать как **условное перемещение (Conditional Move)**. В отличие от безусловного перемещения (Unconditional Move), идеальная пересылка позволяет избежать непредвиденного "украдения" владения переменной из контекста, где это не предполагается. Безусловное перемещение может привести к неожиданным проблемам с владением ресурсами, поэтому в таких случаях предпочтительнее использовать идеальную пересылку.

```cpp
template<typename T>
void f(T&& x); // Forwarding Reference

auto&& var2 = var1; // Forwarding Reference
```

Пересылающие ссылки представляют:
- **Lvalue-ссылку**, если они инициализируются lvalue.
- **Rvalue-ссылку**, если они инициализируются rvalue.

Rvalue-ссылки являются пересылающими ссылками, если:
- **Включают вывод типа**.
- **Используются в форме T&& или auto&&**.

Использование пересылающих ссылок позволяет писать обобщённый код, который может работать с любыми типами аргументов, сохраняя их значимость и избегая ненужных копирований.

### Forwarding References Example

- `Arg&&` - это форвардинг-ссылка (forwarding reference), которая может принимать как lvalue, так и rvalue.
- `std::forward<Arg>(arg)` - это функция, которая сохраняет тип аргумента при пересылке, обеспечивая корректную передачу как lvalue, так и rvalue.

**Детали**

`std::forward` условно преобразует свой вход в rvalue ссылку:
- Если переданное значение является lvalue, оно преобразуется в lvalue ссылку.
- Если переданное значение является rvalue, оно преобразуется в rvalue ссылку.

`std::forward` сам по себе ничего не пересылает.

```cpp
template <typename T>
T&& forward(std::remove_reference_t<T>& t) noexcept {
    return static_cast<T&&>(t);
}
```

**Пример без идеальной пересылки**

Пример кода без идеальной пересылки приводит к ошибке компиляции при передаче rvalue:

```cpp
namespace std {

template<typename T, typename Arg>
unique_ptr<T> make_unique(Arg& arg) {
    return unique_ptr<T>(new T(arg));
}

} // namespace std

std::make_unique<int>(1); // Compilation error, rvalue
```

Ошибка компиляции возникает потому, что `Arg&` не может принять rvalue (например, `1`).

**Решение: Forwarding References**

Forwarding References решает эту проблему, позволяя шаблонным функциям принимать как lvalue, так и rvalue:

```cpp
namespace std {

template<typename T, typename Arg>
unique_ptr<T> make_unique(Arg&& arg) {
    return unique_ptr<T>(new T(std::forward<Arg>(arg)));
}

} // namespace std

std::make_unique<int>(1); // Работает корректно
```

Использование `Arg&&` и `std::forward<Arg>(arg)` позволяет корректно передавать и lvalue, и rvalue, обеспечивая правильное поведение и избежание ошибок компиляции.

### Заметка: Как устроен `std::move`

`std::move` безусловно приводит свой входной параметр к rvalue ссылке. Само `std::move` ничего не перемещает, оно просто преобразует тип.

Пример реализации `std::move`:

```cpp

template <typename T>
std::remove_reference_t<T>&& move(T&& t) noexcept {
    return static_cast<std::remove_reference_t<T>&&>(t);
}

```

Эта реализация показывает, что `std::move` просто преобразует ссылку на объект в rvalue ссылку, что позволяет вызвать соответствующий перемещающий конструктор или перемещающий оператор присваивания.

### Опасности Forwarding References

Пример ниже показывает, как использование forwarding ссылок может вызвать неожиданное поведение.

```cpp
struct Person {
    Person(const std::string& name); // Конструктор (1)

    template <typename T>
    Person(T&& x); // Конструктор (2)
};

int main() {
    Person p1("Bjarne"); // Вызовет конструктор (2), тип аргумента char[7]
    std::string name("Herb");
    Person p2(name); // Вызовет конструктор (2), тип аргумента не const
    Person p3(p1); // Вызовет конструктор (2), тип аргумента не const, не вызовется конструктор копирования
}
```

- `Person p1("Bjarne");` вызовет конструктор (2), так как тип аргумента `char[7]`.
- `Person p2(name);` вызовет конструктор (2), потому что тип аргумента `std::string`, который не является const.
- `Person p3(p1);` вызовет конструктор (2), так как тип аргумента `Person`, который не является const, и не вызовет конструктор копирования.

### Overloading set using Forwarding References

Пример ниже показывает, как перегрузка функций с использованием forwarding ссылок может привести к вызову различных функций в зависимости от типа передаваемого аргумента.

```cpp
// Функция с lvalue ссылкой (1)
void f(Widget&);

// Функция с lvalue ссылкой на const (2)
void f(const Widget&);

// Функция с rvalue ссылкой (3)
void f(Widget&&);

// Функция с rvalue ссылкой на const (4)
void f(const Widget&&);

// Шаблон функции с forwarding ссылкой (5)
template <typename T>
void f(T&&);

// Шаблон функции с rvalue ссылкой на const (6)
template <typename T>
void f(const T&&);

Widget getWidget();

void g() {
    f(getWidget()); // Вызовет функцию в зависимости от типа возвращаемого значения getWidget().
}
```

### `std::move` may prevent Return Value Optimization (RVO)

В этом примере показано, как избыточный вызов `std::move` может предотвратить оптимизацию возврата значений (RVO).

```cpp
template <typename... Args>
std::unique_ptr<Widget> create(Args&&... args) {
    auto uptr = std::make_unique<Widget>(std::forward<Args>(args)...);
    return std::move(uptr); // Предотвращает RVO
}
```

**Объяснение**

- Внутри функции `create` мы создаем уникальный указатель `uptr` с помощью `std::make_unique`.
- Затем мы вызываем `std::move(uptr)` при возврате значения, что приводит к предотвращению RVO.
- В результате создается лишний объект, так как компилятор не сможет применить оптимизацию возврата значений.

**Решение**

Чтобы избежать этой проблемы и позволить компилятору использовать RVO, просто верните `uptr` без вызова `std::move`:

```cpp
template <typename... Args>
std::unique_ptr<Widget> create(Args&&... args) {
    auto uptr = std::make_unique<Widget>(std::forward<Args>(args)...);
    return uptr; // Позволяет RVO
}
```

### Copy-and-Swap to the Rescue!

```cpp
NaiveVector& NaiveVector::operator=(const NaiveVector& rhs) {
    NaiveVector copy(rhs);
    copy.swap(*this);
    return *this;
}
```

- **Explanation**:
  - **Complete Copy**: We create a complete copy of `rhs` before making any modifications to `*this`.
  - **Safe Swapping**: This ensures that any aliasing relationship between `rhs` and `*this` cannot cause issues.
  - **Strong Exception Guarantee**: The copy-and-swap idiom provides a strong exception guarantee, as the swap is noexcept.

**Benefits of Copy-and-Swap**

- **Safety**: Guarantees that `*this` will be in a valid state even if an exception is thrown.
- **Simplicity**: Simplifies the implementation of the copy assignment operator.
- **Reuse**: Reuses the copy constructor, reducing code duplication.

### Copy-and-Swap приводит к дублированию

Вместо написания двух операторов присваивания, код которых почти идентичен:

```cpp
// Оператор присваивания для копирования
NaiveVector& NaiveVector::operator=(const NaiveVector& rhs) {
    NaiveVector copy(rhs);
    copy.swap(*this);
    return *this;
}

// Оператор присваивания для перемещения
NaiveVector& NaiveVector::operator=(NaiveVector&& rhs) {
    NaiveVector copy(std::move(rhs));
    copy.swap(*this);
    return *this;
}
```

### By-Value Assignment Operator

Ниже представлен пример, как можно заменить дублирование кода в операторах copy-and-swap для копирования и перемещения, используя один оператор присваивания, который принимает объект по значению:

```cpp
NaiveVector& NaiveVector::operator=(NaiveVector copy) {
    copy.swap(*this);
    return *this;
}
```

1. **Идея**: Вместо двух отдельных операторов присваивания (для копирования и перемещения) мы используем один, который принимает объект по значению. Это позволяет избежать дублирования кода.

2. **Проблемы**: Такое решение редко используется, так как STL обычно реализует операторы копирования и перемещения отдельно. Это может привести к ошибкам, если не будет правильно применяться.

### Правило четырех с половиной (Rule of Four and a Half)

Если ваш класс напрямую управляет каким-либо ресурсом (например, указателем), то для корректности и производительности вам, возможно, придется вручную написать четыре специальные функции-члена:

1. **Деструктор** для освобождения ресурса.
2. **Конструктор копирования** для копирования ресурса.
3. **Конструктор перемещения** для передачи владения ресурсом.
4. **Оператор присваивания по значению** для освобождения ресурса у объекта слева и передачи владения от объекта справа.

Плюс дополнительная половина:

5. **Функция swap** (не член класса, и желательно также версия-член класса) для обмена содержимым объектов.

```cpp

class ResourceManagingClass {
    int* ptr_;
    size_t size_;

public:
    // Деструктор
    ~ResourceManagingClass() {
        delete[] ptr_;
    }

    // Конструктор копирования
    ResourceManagingClass(const ResourceManagingClass& other)
        : ptr_(new int[other.size_]), size_(other.size_) {
        std::copy(other.ptr_, other.ptr_ + size_, ptr_);
    }

    // Конструктор перемещения
    ResourceManagingClass(ResourceManagingClass&& other) noexcept
        : ptr_(other.ptr_), size_(other.size_) {
        other.ptr_ = nullptr;
        other.size_ = 0;
    }

    // Оператор присваивания по значению
    ResourceManagingClass& operator=(ResourceManagingClass other) {
        other.swap(*this);
        return *this;
    }

    // Функция swap
    friend void swap(ResourceManagingClass& first, ResourceManagingClass& second) noexcept {
        using std::swap;
        swap(first.ptr_, second.ptr_);
        swap(first.size_, second.size_);
    }
};
```

Эти функции обеспечивают правильное управление ресурсами, избегая утечек памяти и обеспечивая эффективное перемещение и копирование объектов.

### Complete Vector Implementation with Comments

```cpp
class Vec {
    int* ptr_;
    size_t size_;

public:
    // Copy constructor to copy the resource and avoid double-frees
    Vec(const Vec& rhs)
        : ptr_(new int[rhs.size_]), size_(rhs.size_) {
        std::copy(rhs.ptr_, rhs.ptr_ + size_, ptr_);
    }

    // Move constructor to transfer ownership of the resource, cheaper than copying
    Vec(Vec&& rhs) noexcept
        : ptr_(std::exchange(rhs.ptr_, nullptr)), size_(std::exchange(rhs.size_, 0)) {}

    // Destructor to free the resource and avoid leaks
    ~Vec() {
        delete[] ptr_;
    }

    // Copy-and-swap idiom for the assignment operator
    Vec& operator=(Vec copy) {
        copy.swap(*this);
        return *this;
    }

    // Non-member swap function to make your type swappable efficiently
    friend void swap(Vec& a, Vec& b) noexcept {
        using std::swap;
        swap(a.ptr_, b.ptr_);
        swap(a.size_, b.size_);
    }

    // Member swap function for simplicity
    void swap(Vec& rhs) noexcept {
        using std::swap;
        swap(ptr_, rhs.ptr_);
        swap(size_, rhs.size_);
    }
};
```

1. **Copy Constructor**:
   - Copies the resource from another instance, allocating new memory and copying the elements.
   - Ensures that each `Vec` instance manages its own copy of the data to avoid double-frees.

2. **Move Constructor**:
   - Transfers ownership of the resource from another instance, leaving the source in a valid, but unspecified state.
   - This is more efficient than copying since it only involves pointer manipulation.

3. **Destructor**:
   - Frees the allocated memory to avoid memory leaks.
   - Ensures that the resource is properly cleaned up when the instance is destroyed.

4. **Assignment Operator (Copy-and-Swap Idiom)**:
   - Uses the copy-and-swap idiom to implement the assignment operator.
   - This approach is safe and ensures strong exception safety by creating a copy first and then swapping.

5. **Non-Member Swap Function**:
   - Provides a non-member `swap` function to make `Vec` efficiently swappable.
   - Utilizes `std::swap` to exchange the resources of two `Vec` instances.

6. **Member Swap Function**:
   - Implements a member `swap` function for convenience and efficiency.
   - Swaps the internal pointers and sizes of the two instances using `std::swap`.

### Perfect Forwarding and Universal References (Josuttis Explanation)

```cpp
class Cust {
private:
    std::string first;
    std::string last;
    int id;

public:
    template <typename S1, typename S2>
    Cust(S1&& f, S2&& l = "", int i = 0)
        : first(std::forward<S1>(f)), last(std::forward<S2>(l)), id(i) {}

    // Other members...
};
```

1. **Universal/Forwarding References**:
   - `S1&&` and `S2&&` are universal references in the context of a template. They can bind to both lvalues and rvalues.
   - They are used to implement perfect forwarding, allowing the constructor to forward arguments to member initializers without unnecessary copies.

2. **Perfect Forwarding with `std::forward`**:
   - `std::forward<S1>(f)` and `std::forward<S2>(l)` are used to perfectly forward the arguments `f` and `l` to the member initializers `first` and `last`.
   - `std::forward` is a conditional cast that preserves the value category (lvalue or rvalue) of the arguments.

3. **Constructor Template**:
   - The constructor template accepts two parameters of types `S1` and `S2`. These parameters are forwarded to the `first` and `last` member initializers.
   - The default value for `S2` is an empty string, allowing the constructor to be called with one or two string arguments.

4. **Covers Multiple Constructor Scenarios**:
   - This single constructor template can cover various combinations of `std::string`, `const std::string&`, `std::string&&`, `const char*`, etc., without explicitly defining multiple overloaded constructors.

**Benefits**

- Reduces code duplication by combining multiple constructors into a single template.
- Ensures efficient and correct forwarding of arguments, avoiding unnecessary copies.
- Simplifies the class interface by handling various input types seamlessly.

This example illustrates the power and flexibility of perfect forwarding and universal references in modern C++. By using templates and `std::forward`, we can create constructors that handle a wide range of argument types efficiently and correctly.

### Explanation of the Slide with `enable_if` and SFINAE in C++17

- The slide demonstrates how to use SFINAE and `std::enable_if` to selectively enable a template constructor based on the type of the arguments.
- This technique is useful for avoiding ambiguous constructor calls and ensuring that certain constructors are only used with specific types.
- The C++17 feature `std::enable_if_t` provides a cleaner syntax compared to the earlier standards.

```cpp
class Cust {
private:
    std::string first;
    std::string last;
    int id;

public:
    // Template constructor with SFINAE to enable only if S1 is not Cust
    template <typename S1, typename S2 = std::string,
              typename = std::enable_if_t<!std::is_same_v<S1, Cust>>>
    Cust(S1&& f, S2&& l = "", int i = 0)
        : first(std::forward<S1>(f)), last(std::forward<S2>(l)), id(i) {}
};
```

**Key Points**

1. **SFINAE with `std::enable_if`**:
   - `std::enable_if` is used to conditionally enable the template constructor.
   - `std::enable_if_t<!std::is_same_v<S1, Cust>>` ensures that the constructor is enabled only if `S1` is not `Cust`.
   - `std::is_same_v<S1, Cust>` is a shorthand for `std::is_same<S1, Cust>::value`, which checks if `S1` is the same type as `Cust`. The `!` negates the result, so the constructor is enabled if `S1` is **not** `Cust`.

2. **Perfect Forwarding**:
   - `S1&&` and `S2&&` are universal/forwarding references, allowing the constructor to accept both lvalues and rvalues.
   - `std::forward<S1>(f)` and `std::forward<S2>(l)` are used to forward the arguments `f` and `l` to the member initializers `first` and `last`.

3. **Constructor Definition**:
   - The constructor template can take any type `S1` for the first parameter and `S2` (defaulting to `std::string`) for the second parameter.
   - The default value for `S2` is an empty string, allowing the constructor to be called with one or two string arguments.

**Example Usage**

```cpp
Cust c("Joe", "Fix", 42);  // Uses the template constructor with S1 = const char*
Cust f("Nico");            // Uses the template constructor with S1 = const char*, S2 defaults to std::string

Cust g(f);                 // Error: The constructor is not enabled for S1 = Cust
const Cust cc("Jim");      // Uses the template constructor with S1 = const char*, S2 defaults to std::string
Cust h(cc);                // Error: The constructor is not enabled for S1 = Cust
```

### Функторы быстрее указателей в Лямбда-выражениях

1. **Инлайн-функции и оптимизация**:
   - **Функторы**: Поскольку функторы представляют собой объекты с перегруженным оператором `operator()`, компилятор может инлайнить вызовы этого оператора. Это устраняет накладные расходы на вызов функции и позволяет компилятору оптимизировать код лучше.
   - **Указатели на функции**: Указатели на функции вызывают накладные расходы, связанные с вызовом через указатель, что предотвращает инлайнинг и, как следствие, уменьшает возможность компилятора оптимизировать код.

2. **Кэширование и предсказание ветвлений**:
   - **Функторы**: Код вызова функтора находится в одном месте, и это помогает процессору предсказывать ветвления более эффективно. Также это уменьшает вероятность кэш-промахов.
   - **Указатели на функции**: Вызовы через указатель на функцию могут ухудшить предсказание ветвлений процессором, так как адрес вызываемой функции может меняться.

3. **Типизация и специализация**:
   - **Функторы**: Поскольку тип функтора известен на этапе компиляции, компилятор может генерировать специализированный код для конкретного типа функтора, что улучшает производительность.
   - **Указатели на функции**: В случае указателей на функции компилятор не может провести такую же специализацию, так как указатель может указывать на любую функцию с соответствующей сигнатурой.

4. **Передача параметров**:
   - **Функторы**: Функторы могут быть оптимально переданы по ссылке или значению, что позволяет избежать лишних копирований.
   - **Указатели на функции**: Передача указателя на функцию всегда требует разыменования указателя, что добавляет дополнительные операции.

```cpp
#include <vector>
#include <algorithm>

// Функтор
struct Less {
    bool operator()(int a, int b) const {
        return a < b;
    }
};

// Указатель на функцию
bool lessFunction(int a, int b) {
    return a < b;
}

int main() {
    std::vector<int> vec = {4, 2, 3, 1, 5};

    // Использование функтора
    std::sort(vec.begin(), vec.end(), Less());

    // Использование указателя на функцию
    std::sort(vec.begin(), vec.end(), lessFunction);

    return 0;
}
```

### Указатели на методы классов

```cpp
struct MyClass {
    int DoIt(float a, int b) const;
};

using constif_t = int (MyClass::*)(float, int) const;

// Поддерживается два синтаксиса вызова
constif_t ptr = &MyClass::DoIt;

MyClass c;
(c.*ptr)(1.0, 1);  // Вызов через объект

MyClass* pc = &c;
(pc->*ptr)(1.0, 1);  // Вызов через указатель на объект
```

### Fold Expressions

Свёртка выражений позволяет компактно записывать операции над вариативным числом аргументов шаблонов, применяя заданную операцию ко всем аргументам.

1. **Fold Expressions (Свёртка выражений)**
   - Свёртка выражений помогает упростить код, когда необходимо применить одну и ту же операцию ко всем элементам набора аргументов шаблона.
   - В C++17 были добавлены два вида свёртки: свёртка влево (left fold) и свёртка вправо (right fold).

2. **Коммутативность и ассоциативность**
   - При выборе между левосторонней и правосторонней свёрткой, важным фактором является коммутативность операций, а не ассоциативность.
   - Коммутативность означает, что порядок операндов не влияет на результат операции, тогда как ассоциативность указывает, что порядок выполнения операций не изменяет результат.

3. **Примеры кода**
   - В слайде показаны два шаблона функции, которые демонстрируют, как применять свёртку выражений для умножения матриц:
   - `multiply_on_right`: выполняет правостороннюю свёртку, начиная с первого аргумента и умножая его на остальные аргументы справа налево.
   - `multiply_on_left`: выполняет левостороннюю свёртку, начиная с последнего аргумента и умножая его на остальные аргументы слева направо.

```cpp

template<typename Matrix, typename... Args>
auto multiply_on_right(Matrix&& m, Args&&... args) {
    return (m * ... * args); // Правосторонняя свёртка
}

template<typename Matrix, typename... Args>
auto multiply_on_left(Matrix&& m, Args&&... args) {
    return (args * ... * m); // Левосторонняя свёртка
}

```

В обоих случаях результат умножения будет одинаковым (24), но порядок выполнения операций разный:
- **Правосторонняя свёртка:** `(a * b) * c`
- **Левосторонняя свёртка:** `a * (b * c)`

Это важно учитывать в случае, если операция не коммутативна и не ассоциативна, так как результат может отличаться в зависимости от порядка выполнения операций.

### chrono DATES

```cpp

using namespace std::chrono;

constexpr auto today_us = September/25/2018;
constexpr auto today_uk = 25d/September/2018;
constexpr auto today = 2018y/September/25;

```

In this example, the `std::chrono` namespace is used to define date literals in different formats. The DSL (Domain-Specific Language) allows for clear and concise date definitions using user-defined literals (UDLs) and the `/` operator to separate day, month, and year.

### Таблица виртуальных функций (vtable)

- При создании класса с хотя бы одним виртуальным методом в него добавляется vptr.
- Конструктор базового класса динамически выделяет память для таблицы виртуальных функций.
- Конструктор каждого потомка производит инициализацию её своими методами. В итоге там всегда оказываются нужные указатели.

### Empty Base Class Optimizations (EBCO)

- Оптимизация пустого базового класса (EBCO) применяется когда базовый класс хм... пустой.

```cpp

class A {};
class B : public A {};
A a; assert(sizeof(a) == 1);
B b; assert(sizeof(b) == 1);

```

- Заметьте, класс с хотя бы одним виртуальным методом точно не пустой.
- Пока неясно зачем нам вообще такие ребята. Они сыграют позже, так как нужны для так называемых миксинов.

### EBCO и unique_pointer

- Если делетер в unique_pointer это класс, то:

```cpp

template <typename T, typename Deleter = default_delete<T>>
class unique_ptr : public Deleter {
  T *ptr_;

public:
  unique_ptr(T *ptr = nullptr, Deleter del = Deleter()) :
    Deleter(del), ptr_(ptr), del_(del) {}

  ~unique_ptr() { Deleter::operator()(ptr_); }
};

```

- Учти это невозможно если делетер функция (см. пример)

**Пример использования**

```cpp
#include <iostream>
#include <memory>

enum { SZ = 1000 };

struct CDeleter {
    void operator()(int *t) { delete[] t; }
};

auto LDeleter = [](int *t) { delete[] t; };
using LDeleterTy = decltype(LDeleter);

void FDeleter(int *t) { delete[] t; }
using FDeleterTy = decltype(&FDeleter);

int main() {
    int *Uip = new int[SZ]();
    std::unique_ptr<int, CDeleter> Uic(new int[SZ]());
    std::unique_ptr<int, LDeleterTy> Uil(new int[SZ](), LDeleter);
    std::unique_ptr<int, FDeleterTy> Uif(new int[SZ](), FDeleter);

    std::cout
        << "Uip: " << sizeof(Uip)       // 8
        << ", Uic: " << sizeof(Uic)     // 8
        << ", Uil: " << sizeof(Uil)     // 8 ???
        << ", Uif: " << sizeof(Uif)     // 16
        << std::endl;

    delete[] Uip;
}
```

### Аргументы по умолчанию связываются статически (важно для виртуальных методов)

Аргументы по умолчанию в C++ связываются статически и зависят от статического типа указателя или ссылки, используемой для вызова функции, а не от динамического типа объекта. В приведенном примере, несмотря на то, что объект, на который указывает указатель `pb`, является экземпляром `Derived`, значение аргумента по умолчанию берется из базового класса `Base`, так как тип указателя — `Base*`.

```cpp
struct Base {
    virtual int foo(int a = 14) { return a; }
};

struct Derived : public Base {
    int foo(int a = 42) override { return a; }
};

Base *pb = new Derived();
std::cout << pb->foo() << std::endl; // на экране 14
```

### Non-Virtual Interface (NVI) Pattern - решение проблемы с аргументами по умолчанию для виртуальных методов

Использование идиомы NVI (Non-Virtual Interface) позволяет избежать проблем с аргументами по умолчанию в виртуальных функциях. В этом примере интерфейс `foo` с аргументом по умолчанию невиртуальный, а внутренняя реализация `foo_impl` виртуальная и может быть переопределена в производных классах.
- Закрытая виртуальная функция открыто переопределена. Это нормально

```cpp
struct BaseNVI {
    int foo(int x = 14) { return foo_impl(x); }

private:
    virtual int foo_impl(int a) { return a; }
};

struct Derived : public Base {
    int foo_impl(int a) override { return a; }
};
```

### Pure Virtual Call

- Чтобы сделать PVC (Pure Virtual Call) и избежать предупреждения компилятора и ошибки линковки, можно использовать функцию-посредника, вызываемую в конструкторе. Это приведет к ошибке выполнения.
- Если вызывать виртуальный метод из конструктора, то будет варнинг компилятора и вызов девиртуализуется.
- То же самое касается и деструктора. Потому что в деструкторе виртуальной таблицы уже нет, а в конструкторе все еще нет.

```cpp
#include <iostream>

struct Base {
    Base() { callDoIt(); } // Вызов посредника в конструкторе
    virtual void doIt() = 0;
    void callDoIt() { doIt(); } // Посредник для вызова виртуальной функции
};

struct Derived : public Base {
    void doIt() override { std::cout << "Derived::doIt()" << std::endl; }
};

int main() {
    Derived d; // Здесь произойдет ошибка выполнения, так как вызовется чисто виртуальная функция
}
```

### Два полиморфизма

Полиморфизм в программировании позволяет создавать функции, которые могут обрабатывать данные разных типов, используя один и тот же интерфейс. Статический полиморфизм разрешается во время компиляции, а динамический — во время выполнения программы.

- Полиморфной (по данному аргументу) называется функция, которая ведет себя по-разному в зависимости от типа этого аргумента
- Полиморфизм бывает статический, когда функция управляется известными на этапе компиляции типами и динамический, когда типы известны только на этапе выполнения
- Примеры:
  - **Множество перегрузок** можно рассматривать как одну **статическую** полиморфную функцию (по любому аргументу)
  - **Шаблон функции** это **статическая** полиморфная функция (по любому аргументу)
  - **Виртуальная функция** это **динамическая** полиморфная функция (по первому невидимому аргументу this)

### Перегрузка виртуальных функций

- Предположим, что мы умеем эффективно возводить разреженные матрицы в целые степени и хотим просто переиспользовать возведение в дробные.
- Перегрузка виртуальных функций возможна, однако она может привести к неоднозначностям в коде, как это продемонстрировано в примере на слайде.

```cpp

struct Matrix {
    virtual void pow(double x); // 1. обычный алгоритм для double
    virtual void pow(int x);    // 2. эффективный алгоритм
};

struct SparseMatrix : public Matrix {
    void pow(int x) override;   // 3. крайне эффективный алгоритм
};

SparseMatrix d;
d.pow(1.5); // какой метод будет вызван?

```

- Будет вызван метод 3, т.к. overload set берется из класса SparseMatrix, а не из базового класса Matrix.
- Для исправления этой ситуации можно использовать using:

```cpp

struct Matrix {
    virtual void pow(double x); // 4. обычный алгоритм для double
    virtual void pow(int x);    // 5. эффективный алгоритм
};

struct SparseMatrix : public Matrix {
    using Matrix::pow;          // Втаскиваем оба метода из базового класса
    void pow(int x) override;   // 6. крайне эффективный алгоритм
};

SparseMatrix d;
d.pow(1.5); // какой метод будет вызван?

```

- Теперь будет вызван метод 1, т.к. overload set из класса SparseMatrix включает в себя оба метода из базового класса Matrix.
