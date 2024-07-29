// clang-format off

struct S { struct subtype {}; };

template<typename T>
void foo1 (const T& x) {
    T::subtype *y;
}

template<typename T>
void foo2 (const T& x) {
    typename T::subtype *y;
}

// clang-format on

int main()
{
    foo1<S>(S{});
    foo2<S>(S{});
}