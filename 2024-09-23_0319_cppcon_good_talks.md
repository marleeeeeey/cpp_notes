# CppCon and other conferences - good talks

- [Ben Deane - Deducing this Patterns, CppCon - 2021](#ben-deane---deducing-this-patterns-cppcon---2021)

## Ben Deane - Deducing this Patterns, CppCon - 2021

- https://www.youtube.com/watch?v=jXf--bazhJw

В примере ниже показано, что CRTP техника может быть заменена на deducing this pattern.

```cpp
struct NumericalFunctions {
    template <typename Self>
    void scale(this Self&& self, double multiplicator) {    // <=== Тут происходид затаскивание ПРОИЗВОДНОГО
        self.setValue(self.getValue() * multiplicator);     //      класса под self. Это очень важно, и именно это
    }                                                       //      позволяет делать магию с CRTP. Это основная идея.
};

struct Sensitivity : NumericalFunctions {
    double getValue() const;
    void setValue(double value);
};
