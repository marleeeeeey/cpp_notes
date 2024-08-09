### Написать Lazy строку за 15 минут.

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

### Напишите для `basic_string` сравнение (`operator==`)

- Напишите для `basic_string` сравнение (`operator==`).
- Сделаете ли вы этот оператор методом класса или свободной функцией?
- Как должны сравниваться строки с одинаковым `CharT`, но разными `Traits`?
- А если у них одинаковые `CharT` и `Traits`, но разные аллокаторы?

#### Решение

1. **Реализация оператора сравнения**:

```cpp
template <typename CharT,
          typename Traits = std::char_traits<CharT>,
          typename Allocator = std::allocator<CharT>>
class basic_string {
public:
    // Конструкторы, деструкторы и другие методы

    bool operator==(const basic_string& other) const {
        if (this == &other) {
            return true;
        }
        if (size_ != other.size_) {
            return false;
        }
        return Traits::compare(data_, other.data_, size_) == 0;
    }

private:
    CharT* data_;
    std::size_t size_;
    std::size_t capacity_;
    Allocator allocator_;
};
```

2. **Свободная функция для сравнения**:

```cpp
template <typename CharT, typename Traits, typename Allocator>
bool operator==(const basic_string<CharT, Traits, Allocator>& lhs,
                const basic_string<CharT, Traits, Allocator>& rhs) {
    if (&lhs == &rhs) {
        return true;
    }
    if (lhs.size() != rhs.size()) {
        return false;
    }
    return Traits::compare(lhs.data(), rhs.data(), lhs.size()) == 0;
}
```

#### Обсуждение вопросов

1. **Метод класса или свободная функция**:
   - Метод класса удобен, так как он имеет доступ ко всем членам класса.
   - Свободная функция предоставляет более гибкий интерфейс и может использоваться в более широком контексте.

2. **Сравнение строк с одинаковым `CharT`, но разными `Traits`**:
   - Если `Traits` различаются, строки должны считаться различными, так как `Traits` определяет, как символы сравниваются между собой.

3. **Сравнение строк с одинаковыми `CharT` и `Traits`, но разными аллокаторами**:
   - Аллокаторы влияют на управление памятью, но не на содержимое строк. Поэтому строки с одинаковым содержимым должны считаться равными, даже если у них разные аллокаторы.
