#include <iostream>

/*
Example of CRTP(Curiously Recurring Template Pattern) for
1. extending a class with a mixin.
2. implementing static polymorphism (interface).
Read more: https://github.com/marleeeeeey/cpp_notes/blob/main/2024-09-23_0209_fluent_cpp_blog_notes.md
*/

// ************* 1. extending a class with a mixin. *************

template <typename T>
struct Caclulations
{
    void scale(int factor)
    {
        T& underlying = static_cast<T&>(*this);
        underlying.setValue(underlying.getValue() * factor);
    }
};

class Pressure : public Caclulations<Pressure>
{
    int value_;
public:
    Pressure(int value) : value_(value) {}
    int getValue() const { return value_; }
    void setValue(int value) { this->value_ = value; }
};

// ***** 2. implementing static polymorphism (interface). *****

template <typename T>
class Amount
{
public:
    double getValue() const { return static_cast<T const&>(*this).getValue(); }
};

class Variable : public Amount<Variable>
{
public:
    explicit Variable(int value) : value_(value) {}
    double getValue() const { return value_; }
private:
    int value_;
};

template <typename T>
void print(Amount<T> const& amount)
{
    std::cout << amount.getValue() << '\n';
}

// *************************** main ***************************

int main()
{
    Pressure p(10);
    std::cout << "Before: p.getValue()=" << p.getValue() << std::endl;
    p.scale(2);
    std::cout << "After:  p.getValue()=" << p.getValue() << std::endl;

    Variable v(43);
    print(v);
}