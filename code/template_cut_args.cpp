// clang-format off

template <typename T>
T max(T x, T y) { return x > y ? x : y; }

// clang-format on

int main()
{
    const int& b = 1;
    const int c = 2;
    int a = max(b, c);

    int e = 5;
    const int& d = e;
    a = max(d, e);
}
