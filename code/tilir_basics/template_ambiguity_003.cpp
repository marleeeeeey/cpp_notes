// clang-format off

template<typename T> struct S {
    template<typename U> void foo() {}
};

template<typename T> void bar1() {
    S<T> s;
    s.foo<T>(); // error: use 'template' keyword to treat 'foo' as a dependent template name [-Werror]
}

template<typename T> void bar2() {
    S<T> s;
    s.template foo<T>(); // OK. Use 'template' keyword to treat 'foo' as a dependent template name
}

// clang-format on

int main()
{
    bar1<int>();
    bar2<int>();
}