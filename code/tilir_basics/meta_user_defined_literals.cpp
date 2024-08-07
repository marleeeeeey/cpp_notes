#include <iostream>

class Complex
{
    double re, im;
public:
    constexpr Complex(double r = 0.0, double i = 0.0) : re(r), im(i) {}
    constexpr double real() const { return re; }
    constexpr double imag() const { return im; }
    constexpr Complex operator+=(Complex rhs)
    {
        re += rhs.re;
        im += rhs.im;
        return *this;
    }
    void dump(std::ostream& os) const { os << re << " + " << im << "i"; }
};

constexpr Complex operator+(Complex lhs, Complex rhs)
{
    lhs += rhs;
    return lhs;
}

std::ostream& operator<<(std::ostream& os, Complex rhs)
{
    rhs.dump(os);
    return os;
}

constexpr Complex operator""_i(long double arg)
{
    return Complex{0.0, static_cast<double>(arg)};
}

// clang-format off

int main()
{
    constexpr Complex c = 3.0 + 1.0_i;
    constexpr Complex d = 2.0 + c;      // 5 + 2i
    std::cout << c + d << std::endl;    // 8 + 2i
}

// clang-format on