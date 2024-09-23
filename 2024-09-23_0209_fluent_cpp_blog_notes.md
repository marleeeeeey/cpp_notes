# Jonathan Boccara - Fluent C++ Blog Notes

- [About the author](#about-the-author)
- [Jonathan Boccara - The Curiously Recurring Template Pattern (CRTP) - 2017](#jonathan-boccara---the-curiously-recurring-template-pattern-crtp---2017)
  - [Зачем нам нужен CRTP?](#зачем-нам-нужен-crtp)
  - [Что нам дает CRTP?](#что-нам-дает-crtp)

## About the author

https://www.fluentcpp.com

## Jonathan Boccara - The Curiously Recurring Template Pattern (CRTP) - 2017

- https://www.fluentcpp.com/2017/05/12/curiously-recurring-template-pattern/
- https://www.fluentcpp.com/2017/05/16/what-the-crtp-brings-to-code/
- https://www.fluentcpp.com/2017/04/28/extract-interface-cpp/

### Зачем нам нужен CRTP?

- Чтобы иметь доступ к методам класса наследника внутри базового класса (`T& underlying = static_cast<T&>(*this);`).

### Что нам дает CRTP?

1. Дает возможность **добавить функциональности** к классу. Похожее можно сделать и через свободные функции, но они часто теряются за инклюдами и не видны в интерфейсе класса. Класс наследник расширяет свой интерфейс наследуясь от базового класса для того, чтобы добавить функциональности. Производный класс предлагает интерфейс базовому классу.

```cpp
template <typename T>
struct NumericalFunctions
{
    void scale(double multiplicator)
    {
        T& underlying = static_cast<T&>(*this);
        underlying.setValue(underlying.getValue() * multiplicator);
    }
    void square()
    {
        T& underlying = static_cast<T&>(*this);
        underlying.setValue(underlying.getValue() * underlying.getValue());
    }
    void setToOpposite()
    {
        scale(-1);
    };
};

class Sensitivity : public NumericalFunctions<Sensitivity>
{
public:
    double getValue() const;
    void setValue(double value);
    // rest of the sensitivity's rich interface...
};
```

2. Использовать **статический интерфейс** для класса. Один класс предоставляет интерфейс, а класс наследник предоставляет реализацию. При этом виртуальные функции не используются.

```cpp
template <typename T>
class Amount
{
public:
    double getValue() const
    {
        return static_cast<T const&>(*this).getValue();
    }
};

class Constant42 : public Amount<Constant42>
{
public:
    double getValue() const {return 42;}
};

class Variable : public Amount<Variable>
{
public:
    explicit Variable(int value) : value_(value) {}
    double getValue() const {return value_;}
private:
    int value_;
};

template<typename T>
void print(Amount<T> const& amount)
{
    std::cout << amount.getValue() << '\n';
}

Constant42 c42;
print(c42);         // 42
Variable v(43);
print(v);           // 43
```
