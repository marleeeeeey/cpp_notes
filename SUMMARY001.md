- [Введение в RVO и копирование/перемещение](#введение-в-rvo-и-копированиеперемещение)
- [Move Assignment Operator](#move-assignment-operator)
- [Правило 0 и правило 5](#правило-0-и-правило-5)
- [Perfect forwarding](#perfect-forwarding)
- [Примеры использования `std::forward`](#примеры-использования-stdforward)
- [Введение в RVO](#введение-в-rvo)

### Введение в RVO и копирование/перемещение

- **Copy elision** (устранение копирования): часть стандарта; разрешено.
- **Temporary materialization** (временная материализация): часть стандарта; обязательно.
- **URVO и NRVO**: неофициальные термины.
- **Implicit move** (неявное перемещение): RVO, которое происходит даже без устранения копирования.
- prvalues не перемещаются.

### Move Assignment Operator

В случае оператора перемещения самоприсваивание обычно не проверяется, потому что:
- Временное значение создается для присваивания, поэтому самоприсваивание происходит редко.
- Наличие самоприсваивания делает код менее оптимизированным.
- Временное значение не требует очистки.

### Правило 0 и правило 5

- **Правило 0**: Не определяйте никаких операторов и конструкторов, компилятор сделает это за вас.
- **Правило 5**: Если вы определяете деструктор, конструктор копирования или оператор присваивания, то правило 6. Включает также конструктор перемещения и оператор перемещения.

### Perfect forwarding

- **Perfect forwarding** (идеальная пересылка) позволяет передавать аргументы, сохраняя их исходные квалификаторы.
- Использование `std::forward` для условного приведения аргументов к lvalue или rvalue.

```cpp
template<typename T>
T&& forward(std::remove_reference_t<T>& t) noexcept {
    return static_cast<T&&>(t);
}
```

### Примеры использования `std::forward`

#### Без Perfect forwarding

```cpp
namespace std {
    template<typename T, typename Arg>
    unique_ptr<T> make_unique(Arg const& arg) {
        return unique_ptr<T>(new T(arg));
    }
}

// Пример:
int i{ 1 };
std::make_unique<Example>(i); // Always adds const
```

#### Perfect forwarding

```cpp
namespace std {
    template<typename T, typename... Args>
    unique_ptr<T> make_unique(Args&&... args) {
        return unique_ptr<T>(new T(std::forward<Args>(args)...));
    }
}
```

#### Механика `std::forward`

- Условное приведение к lvalue или rvalue в зависимости от входного значения.

```cpp
template<typename T>
T&& forward(std::remove_reference_t<T>& t) noexcept {
    return static_cast<T&&>(t);
}
```

### Введение в RVO

- **RVO** (Return Value Optimization): техника оптимизации, устраняющая копирование возвращаемого значения.
- **Temporary materialization**: обязательная часть стандарта, которая обеспечивает правильную работу временных объектов.
