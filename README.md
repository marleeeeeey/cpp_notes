- [Not Sorted Notes](#not-sorted-notes)
- [Заметка о RVO и конструкторах копирования](#заметка-о-rvo-и-конструкторах-копирования)
- [Заметка о volatile](#заметка-о-volatile)
- [Про `operator->`](#про-operator-)
- [Заметка про R-Value и L-Value ссылки и выражения. `std::move`](#заметка-про-r-value-и-l-value-ссылки-и-выражения-stdmove)
- [Note on Move Semantics and `std::exchange`](#note-on-move-semantics-and-stdexchange)

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

- В контексте move-семантики удобно использовать **`std::exchange`, чтобы обмениваться значениями**,
- и желательно указывать атрибут **`noexcept`** для move функций, если они не выкидывают исключений. Это **ускорит работу библиотечными контейнерами**.

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
