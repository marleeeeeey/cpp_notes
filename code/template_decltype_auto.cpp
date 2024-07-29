// clang-format off

int main()
{
    double x = 1.0;
    decltype(x) tmp1 = x;       // -> double
    decltype(auto) tmp2 = x;    // -> double (without code duplication)
    decltype(auto) tmp3 = (x);  // -> double&
}

// clang-format on